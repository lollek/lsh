#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#include "string.h"
#include "io.h"

#include "command.h"
#include "command/help.h"
#include "command/cd.h"
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

    if (cmd[0] == '@')
      {
        if (stdout_set(cmd + 1) != 0)
            return ERROR;
        ++(*argsptr);
        return redirect_fds(argsptr);
      }
    if (cmd[0] == '#')
      {
        if (stderr_set(cmd + 1) != 0)
            return ERROR;
        ++(*argsptr);
        return redirect_fds(argsptr);
      }

    return ACTIONS_PENDING;
  }

static void
restore_fds(void)
  {
    stdout_reset();
    stderr_reset();
  }

static status_t
builtin(char **argv)
  {
    if (!strcmp(argv[0], "cd"))
        command_cd(argv);
    else if (!strcmp(argv[0], "help"))
        help(argv[1]);
    else if (!strcmp(argv[0], "exit"))
        return ACTION_EXIT;
    else if (!strcmp(argv[0], "path"))
        command_path(argv);
    else
        return ACTIONS_PENDING;
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
eval(const char *cmd)
  {
    status_t status = ACTIONS_PENDING;
    char **args, **orig_args;

    if (cmd == NULL)
        return 2;
    if (cmd[0] == '\0')
        return 0;

    orig_args = args = splits(cmd, ' ');
    if (args == NULL)
      {
        fprintf(stderr, "Virtual memory exhausted\n");
        return 1;
      }

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
