#include <stdio.h>
#include <stdlib.h>

#include "argparse.h"
#include "lineread.h"
#include "command.h"

int main(int argc, char *argv[])
  {
    parse_arguments(argc, argv);

    while (eval(read_line("> ")) == 0)
      ;

    return 0;
  }
