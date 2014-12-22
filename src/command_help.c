#include <stdio.h>
#include <string.h>

#include "command_help.h"

static void
all_help(void)
  {
    printf("Builtin commands:\n"
           "\texit"
           "\thelp"
           "\n");
  }

void
help(const char *cmd)
  {
    if (cmd == NULL)
        all_help();
    else if (!strcmp(cmd, "exit"))
        puts("Exit lsh");
    else
        printf("No help for '%s'\n", cmd);
  }
