#include <stdio.h>
#include <stdlib.h>

#include "argparse.h"
#include "lineread.h"

int main(int argc, char *argv[])
  {
    parse_arguments(argc, argv);

    while (1)
      {
        char *line = read_line("> ");
        if (line != NULL)
          {
            puts(line);
            free(line);
          }
      }

    return 0;
  }
