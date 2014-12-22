#include <stdio.h>
#include <stdlib.h>

#include "lineread.h"
#include "command.h"
#include "path.h"

int
main(void)
  {
    int status = 0;

    /* Init */
    if (init_path() != 0)
        exit(1);

    /* Loop */
    while (status == 0)
      {
        char *line = read_line("> ");
        status = eval(line);
        free(line);
      }

    /* Exit */
    exit_path();

    return status;
  }
