#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <errno.h>

#include "string.h"
#include "path.h"

#include "command.h"
#include "command_help.h"

typedef enum status_t
  {
    NONE,
    OK,
    EXIT_FAIL,
    EXIT_OK
  }
status_t;

/**
 * Builtins
 * exit / logout - exit lsh
 */
static void
builtin(status_t *status, char *arg0, char **argv)
  {
    *status = OK;
    if (!strcmp(arg0, "help"))
        help(argv[1]);
    else if (!strcmp(arg0, "exit"))
        *status = EXIT_OK;
    else
        *status = NONE;
  }

static bool
execable(char *path)
  {
    struct stat info;
    if (access(path, F_OK)
        || access(path, X_OK)
        || lstat(path, &info) != 0)
        return false;
    if (S_ISDIR(info.st_mode))
      {
        errno = EISDIR;
        return false;
      }
    return true;
  }

static int
forkexec(char *arg0, char **argv)
  {
    pid_t pid;
    switch(pid = fork())
      {
        case -1: perror("fork"); break;
        case 0: execv(arg0, argv); break;
        default: waitpid(pid, NULL, 0); break;
      }
    return 0;
  }

int
eval(const char *cmd)
  {
    status_t status = NONE;
    char **args;

    if (cmd == NULL)
        return 2;
    if (cmd[0] == '\0')
        return 0;

    args = splits(cmd, ' ');
    if (args == NULL)
      {
        fprintf(stderr, "Error %s L%d: splits(%s) == NULL!\n",
                __FILE__, __LINE__, cmd);
        return 1;
      }

    /* Builtins */
    builtin(&status, args[0], args);

    /* Relative path */
    if (status == NONE && strchr(args[0], '/'))
      {
        if (execable(args[0]))
            forkexec(args[0], args);
        else
            perror(args[0]);

        status = OK;
      }

    /* Inside a path in paths */
    if (status == NONE)
      {
        char **paths = splits(get_path(), ':');
        size_t arg0len = strlen(args[0]);
        size_t i;

        for (i = 0; paths[i] != NULL; ++i)
          {
            size_t pathlen = strlen(paths[i]);
            char *oldarg0 = args[0];
            char *tmparg0 = malloc(arg0len + 1 + pathlen + 1);
            if (tmparg0 == NULL)
              {
                perror("malloc");
                continue;
              }
            strcpy(tmparg0, paths[i]);
            strcpy(tmparg0 + pathlen, "/");
            strcpy(tmparg0 + pathlen + 1, args[0]);
            args[0] = tmparg0;

            if (execable(args[0]))
              {
                forkexec(args[0], args);
                status = OK;
              }

            args[0] = oldarg0;
            free(tmparg0);
          }

        freesplits(paths);
      }

    if (status == NONE)
        printf("Unknown command '%s'\n", args[0]);

    freesplits(args);

    switch (status)
      {
        case EXIT_FAIL: return 1;
        case EXIT_OK: return 2;
        default: return 0;
      }
  }
