#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "cd.h"

#define fail(string) \
    return (!!fprintf(stderr, "cd: %s: %s\n", argv[i], string))


int
command_cd(char * const *argv)
  {
    int i;
    struct passwd *pw;

    for (i = 1; argv[i] != NULL; ++i)
    {
      if (argv[i][0] == '-')
          fail("Invalid option");
      if (chdir(argv[i]))
          fail(strerror(errno));
      else
          return 0;
    }

    if ((pw = getpwuid(getuid())) == NULL)
        fail(strerror(ENOENT));
    if (chdir(pw->pw_dir))
        fail(strerror(errno));
    return 0;
  }
