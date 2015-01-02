#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "io.h"

static int stdout_backup = -1;
static int stderr_backup = -1;

static int
outfile_set(const char *file, int *fd_backup, int fd_to_change)
  {
    const int oflag = O_WRONLY | O_CREAT | O_TRUNC;
    const mode_t omode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    int newfd;

    if ((*fd_backup = dup(fd_to_change)) == -1
        || (newfd = open(file, oflag, omode)) == -1
        || dup2(newfd, fd_to_change) == -1
        || close(newfd))
      {
        perror(file);
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
    if (stdout_backup != -1)
        stdout_reset();
    return outfile_set(file, &stdout_backup, STDOUT_FILENO);
  }

int
stderr_set(const char *file)
  {
    if (stderr_backup != -1)
        stderr_reset();
    return outfile_set(file, &stderr_backup, STDERR_FILENO);
  }

void
stdout_reset(void)
  {
    outfile_reset(&stdout_backup, STDOUT_FILENO);
  }
void
stderr_reset(void)
  {
    outfile_reset(&stderr_backup, STDERR_FILENO);
  }
