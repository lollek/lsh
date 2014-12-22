#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "string.h"

#include "command.h"

static int
help(void)
  {
    printf("Available commands:\n"
           "exit\t-\texit lsh\n"
          );
    return 0;
  }

int
eval(const char *cmd)
  {
    int status = 0;
    char **args = splits(cmd, ' ');
    if (args == NULL)
      {
        fprintf(stderr, "Error %s L%d: splits(%s) == NULL!\n",
                __FILE__, __LINE__, cmd);
        return 1;
      }

    if (!strcmp(cmd, "help"))
        return help();
    else if (!strcmp(cmd, "exit"))
        status = 2;
    else if (!access(args[0], F_OK))
      {
        if (!access(args[0], X_OK))
          {
            pid_t pid;
            switch(pid = fork())
              {
                case -1: perror("fork"); break;
                case 0: execv(args[0], args); break;
                default: waitpid(pid, NULL, 0); break;
              }
          }
        else
            perror(args[0]);
      }
    else
        printf("Unknown command '%s'\n", args[0]);

    freesplits(args);

    return status;
  }
