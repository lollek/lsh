#include <string.h>
#include <stdio.h>

#include "command.h"

static int help(void)
  {
    printf("Available commands:\n"
           "exit\t-\texit lsh\n"
          );
    return 0;
  }

int eval(const char *cmd)
  {
    if (!strcmp(cmd, "help"))
        return help();
    else if (!strcmp(cmd, "exit"))
        return 1;
    else
        printf("Unknown command '%s'\n", cmd);
    return 0;
  }
