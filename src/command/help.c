#include <stdio.h>
#include <string.h>

#include "help.h"

void
help(const char *cmd)
  {
    if (cmd == NULL)
        printf("Builtin commands:\n"
               "\tcd [path]"
               "\texit"
               "\thelp"
               "\tpath"
               "\n");
    else if (!strcmp(cmd, "cd"))
        printf("cd [path]\n"
               "Change directory to path. If no path is given, directory is changed to user's home directory\n");
    else if (!strcmp(cmd, "exit"))
        puts("Exit lsh");
    else if (!strcmp(cmd, "path"))
        puts("Show paths which are searched for programs");
    else
        printf("No help for '%s'\n", cmd);
  }
