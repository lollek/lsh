#include <stdio.h>
#include <stdlib.h>

#include "lineread.h"
#include "command.h"

int
main(void)
  {
    int status = 0;

    while (status == 0)
      {
        char *line = read_line("> ");
        status = eval(line);
        free(line);
      }

    return 0;
  }
