#include <stdio.h>
#include <stdlib.h>

#include "argparse.h"
#include "lineread.h"
#include "command.h"

int main(int argc, char *argv[])
  {
    int status = 0;
    parse_arguments(argc, argv);

    while (status == 0)
      {
        char *line = read_line("> ");
        status = eval(line);
        free(line);
      }

    return 0;
  }
