#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>

#include "../string.h"
#include "path.h"

static char *g_path = NULL;

static bool
execable(const char *path)
  {
    struct stat info;
    if (access(path, F_OK)
        || access(path, X_OK)
        || lstat(path, &info) != 0)
        return false;
    if (S_ISDIR(info.st_mode))
      {
        errno = EISDIR;
        return false;
      }
    return true;
  }


int
command_path_init(const char *given_path)
  {
    const char *path;
    size_t pathlen;

    if (g_path != NULL)
        command_path_exit();

    if (given_path == NULL)
      {
        path = DEFAULT_PATH;
        pathlen = sizeof(DEFAULT_PATH);
      }
    else
      {
        path = given_path;
        pathlen = strlen(given_path);
      }

    g_path = malloc(pathlen + 1);
    if (g_path == NULL)
      {
        fprintf(stderr, "Virtual memory exhausted\n");
        return 1;
      }

    strcpy(g_path, path);
    return 0;
  }

void
command_path_exit(void)
  {
    free(g_path);
    g_path = NULL;
  }

static int
command_path_show(void)
  {
    char **pathv = splits(g_path, ":");
    int i;
    for (i = 0; pathv[i] != NULL; ++i)
        printf("%d: %s\n", i, pathv[i]);
    return 0;
  }

char *
command_path_find(const char *path)
  {
    char **pathv;
    char *retval = NULL;
    size_t pathlen;
    int i;

    if (path == NULL)
        return NULL;

    if (strchr(path, '/'))
      {
        if (execable(path))
            return strdup(path);
        perror(path);
        return NULL;
      }

    pathv = splits(g_path, ":");
    pathlen = strlen(path);
    for (i = 0; pathv[i] != NULL; ++i)
      {
        size_t dirlen = strlen(pathv[i]);
        char *tmppath = malloc(dirlen + 1 + pathlen + 1);
        if (tmppath == NULL)
          {
            fprintf(stderr, "Virtual memory exceeded\n");
            continue;
          }
        strcpy(tmppath, pathv[i]);
        strcpy(tmppath + dirlen, "/");
        strcpy(tmppath + dirlen + 1, path);

        if (execable(tmppath))
          {
            retval = tmppath;
            break;
          }
        free(tmppath);
      }

    freesplits(pathv);
    if (retval == NULL)
        perror(path);
    return retval;
  }

int
command_path(char **argv)
  {
    int i;

    if (argv[1] == NULL)
        return command_path_show();

    for (i = 1; argv[i] != NULL; ++i)
      {
        char *path = command_path_find(argv[i]);
        if (path == NULL)
            continue;

        printf("%s: %s\n", argv[i], path);
        free(path);
      }
    return 0;
  }
