#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "path.h"

static char *g_path = NULL;

int
init_path(void)
  {
    size_t pathlen = sizeof DEFAULT_PATH;

    g_path = malloc(pathlen + 1);
    if (g_path == NULL)
      {
        perror("malloc");
        return 1;
      }

    strcpy(g_path, DEFAULT_PATH);
    return 0;
  }

char *
get_path(void)
  {
    return g_path;
  }

void
exit_path(void)
  {
    free(g_path);
    g_path = NULL;
  }
