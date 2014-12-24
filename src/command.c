#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#include "string.h"

#include "command.h"
#include "command/help.h"
#include "command/cd.h"
#include "command/path.h"

typedef enum status_t
  {
    NONE,
    OK,
    EXIT_FAIL,
    EXIT_OK
  }
status_t;

static status_t
builtin(char *arg0, char **argv)
  {
    if (!strcmp(arg0, "cd"))
        command_cd(argv);
    else if (!strcmp(arg0, "help"))
        help(argv[1]);
    else if (!strcmp(arg0, "exit"))
        return EXIT_OK;
    else if (!strcmp(arg0, "path"))
        command_path(argv);
    else
        return NONE;
    return OK;
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
    char *path;

    if (cmd == NULL)
        return 2;
    if (cmd[0] == '\0')
        return 0;

    args = splits(cmd, ' ');
    if (args == NULL)
      {
        fprintf(stderr, "Virtual memory exhausted\n");
        return 1;
      }

    /* Builtin */
    if ((status = builtin(args[0], args)) != NONE)
        ;
    /* External program */
    else if ((path = command_path_find(args[0])) != NULL)
      {
        forkexec(path, args);
        free(path);
        path = NULL;
        status = OK;
      }

    freesplits(args);

    switch (status)
      {
        case EXIT_FAIL: return 1;
        case EXIT_OK: return 2;
        default: return 0;
      }
  }
