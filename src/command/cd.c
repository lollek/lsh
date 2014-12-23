#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "cd.h"

int
command_cd(char * const *argv)
  {
    int i;
    struct passwd *pw;

    for (i = 1; argv[i] != NULL; ++i)
    {
      if (argv[i][0] == '-')
        {
          fprintf(stderr, "cd: %s: Invalid option\n", argv[i]);
          return 1;
        }

      if (chdir(argv[i]))
        {
          fprintf(stderr, "cd: %s: %s\n", argv[1], strerror(errno));
          return 1;
        }
      else
          return 0;

    }

    if ((pw = getpwuid(getuid())) == NULL)
      {
        fprintf(stderr, "cd: %s\n", strerror(ENOENT));
        return 1;
      }
    if (chdir(pw->pw_dir))
      {
        fprintf(stderr, "cd: %s: %s\n", argv[1], strerror(errno));
        return 1;
      }
    return 0;
  }
