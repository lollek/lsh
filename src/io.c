#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "io.h"

#define fail(msg) { perror(msg); return 1; }

static int  stdin_backup = -1;
static int stdout_backup = -1;
static int stderr_backup = -1;

static int
outfile_set(const char *file, int *fd_backup, int fd_to_change)
  {
    int newfd;

    if ((*fd_backup = dup(fd_to_change)) == -1)
        fail(file);

    if (!strcmp(file, "@"))
        newfd = STDOUT_FILENO;
    else if (!strcmp(file, "#"))
        newfd = STDERR_FILENO;
    else
      {
        const int oflag = O_WRONLY | O_CREAT | O_TRUNC;
        const mode_t omode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
        if ((newfd = open(file, oflag, omode)) == -1)
          fail(file);
      }

    if (dup2(newfd, fd_to_change) == -1)
        fail(file);
    switch (newfd)
      {
        case STDOUT_FILENO: break;
        case STDERR_FILENO: break;
        default:
            if (close(newfd) == -1)
              fail(file);
            break;
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
stdin_set(const char *file)
  {
    int newfd;

    if (stdin_backup != -1)
        stdin_reset();

    if ((stdin_backup = dup(STDIN_FILENO)) == -1
        || (newfd = open(file, O_RDONLY)) == -1
        || dup2(newfd, STDIN_FILENO) == -1
        || close(newfd) == -1)
      {
        perror(file);
        return 1;
      }
    return 0;
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
stdin_reset(void)
  {
    if (stdin_backup == -1)
        return;
    if (dup2(stdin_backup, STDIN_FILENO) == -1)
        perror("outfile_reset (dup2)");
    if (close(stdin_backup) != 0)
        perror("outfile_reset (close)");
    stdin_backup = -1;
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
