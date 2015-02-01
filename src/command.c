#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#include "string.h"
#include "io.h"

#include "command.h"
#include "command/alias.h"
#include "command/cd.h"
#include "command/help.h"
#include "command/path.h"

typedef enum status_t
  {
    ACTIONS_PENDING,
    NO_MORE_ACTIONS,
    ERROR,
    ACTION_EXIT
  }
status_t;

static status_t
redirect_fds(char ***argsptr)
  {
    char **args = (*argsptr);
    char *cmd = args[0];

    if (cmd == NULL)
        return NO_MORE_ACTIONS;

    switch(cmd[0])
      {
        case '!': if  (stdin_set(cmd + 1) != 0) return ERROR; break;
        case '@': if (stdout_set(cmd + 1) != 0) return ERROR; break;
        case '#': if (stderr_set(cmd + 1) != 0) return ERROR; break;
        default: return ACTIONS_PENDING;
      }

    ++(*argsptr);
    return redirect_fds(argsptr);
  }

static void
restore_fds(void)
  {
    stdin_reset();
    stdout_reset();
    stderr_reset();
  }

static status_t
builtin(char **argv)
  {
    if      (!strcmp(argv[0], "alias"))   command_alias(argv);
    else if (!strcmp(argv[0], "cd"))      command_cd(argv);
    else if (!strcmp(argv[0], "exit"))    return ACTION_EXIT;
    else if (!strcmp(argv[0], "help"))    help(argv[1]);
    else if (!strcmp(argv[0], "path"))    command_path(argv);
    else if (!strcmp(argv[0], "unalias")) command_unalias(argv, true);
    else                                  return ACTIONS_PENDING;
    return NO_MORE_ACTIONS;
  }

static status_t
external(char **argv)
  {
    pid_t pid;
    char *path = command_path_find(argv[0]);

    if (path == NULL)
        return ACTIONS_PENDING;

    switch(pid = fork())
      {
        case -1: perror("fork"); break;
        case 0: execv(path, argv); break;
        default: waitpid(pid, NULL, 0); break;
      }
    free(path);
    return NO_MORE_ACTIONS;
  }

int
eval(char *origcmd)
  {
    status_t status = ACTIONS_PENDING;
    char **args, **orig_args;
    char *cmd;

    if (origcmd == NULL)
        return 2;
    if (origcmd[0] == '\0')
        return 0;

    cmd = command_alias_replace(origcmd, " $");
    orig_args = args = splits(cmd, " $");
    if (args == NULL)
      {
        fprintf(stderr, "Virtual memory exhausted\n");
        return 1;
      }
    if (cmd != origcmd)
        free(cmd);

    /* Step 1, redirect fds */
    if (status == ACTIONS_PENDING)
        status = redirect_fds(&args);

    /* Step 2, run builtins */
    if (status == ACTIONS_PENDING)
        status = builtin(args);

    /* Step 3, run external program */
    if (status == ACTIONS_PENDING)
        status = external(args);

    restore_fds();
    freesplits(orig_args);

    return status == ACTION_EXIT ? 2 : 0;
  }

int
exec_file(char *filename)
  {
    FILE *file = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;

    if (file == NULL)
      {
        perror(filename);
        return 1;
      }

    while (getline(&line, &len, file) != -1)
    {
      char *newline = strrchr(line, '\n');
      if (newline != NULL)
          *newline = '\0';
      if (eval(line) != 0)
          break;
    }

    free(line);
    fclose(file);
    return 0;
  }
