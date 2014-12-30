#include <stdio.h>
#include <unistd.h>

#include "io.h"

static int stdout_old = -1;

int stdout_set(const char *file)
  {
    if (stdout_old != -1)
        stdout_reset();

    if (fflush(stdout) != 0
        || ((stdout_old = dup(STDOUT_FILENO)) == -1)
        || freopen(file, "w", stdout) == NULL)
      {
        perror("stdout_set");
        stdout_reset();
        return 1;
      }
    return 0;
  }

void stdout_reset(void)
  {
    if (stdout_old == -1)
        return;

    if (fflush(stdout) != 0)
        perror("stdout_reset (fflush)");
    if (dup2(stdout_old, STDOUT_FILENO) == -1)
        perror("stdout_reset (dup2)");
    if (close(stdout_old) != 0)
        perror("stdout_reset (close)");
    clearerr(stdout);
    stdout_old = -1;
  }
