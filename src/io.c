#include <stdio.h>
#include <unistd.h>

#include "io.h"

static int stdout_old = -1;
static int stderr_old = -1;

static int
outfile_set(const char *path, int *stored_fd, FILE *file, void (*resetfun)(void))
  {
    int fd = fileno(file);

    if (*stored_fd != -1)
        (*resetfun)();

    fflush(file);
    if ((*stored_fd = dup(fd)) == -1)
      {
        perror(path);
        return 1;
      }

    if (freopen(path, "w", file) == NULL)
      {
        perror(path);
        (*resetfun)();
        return 1;
      }
    return 0;
  }

static void
outfile_reset(int *stored_fd, int fd)
  {
    FILE *file;

    if (*stored_fd == -1)
        return;

    if ((file = fdopen(fd, "w")) != NULL)
        fflush(file);

    if (dup2(*stored_fd, fd) == -1)
        perror("outfile_reset (dup2)");
    if (close(*stored_fd) != 0)
        perror("outfile_reset (close)");

    if ((file = fdopen(fd, "w")) != NULL)
        clearerr(file);
    *stored_fd = -1;
  }

int
stdout_set(const char *file)
  {
    return outfile_set(file, &stdout_old, stdout, stdout_reset);
  }

int
stderr_set(const char *file)
  {
    return outfile_set(file, &stderr_old, stderr, stderr_reset);
  }

void
stdout_reset(void)
  {
    outfile_reset(&stdout_old, STDOUT_FILENO);
  }
void
stderr_reset(void)
  {
    outfile_reset(&stderr_old, STDERR_FILENO);
  }
