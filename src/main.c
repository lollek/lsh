#include <stdlib.h>

#include "lineread.h"
#include "command.h"
#include "path.h"
#include "signal.h"

int
main(void)
  {
    int status = 0;

    /* Init */
    if (init_signals() != 0
        || init_path() != 0)
        return 1;

    /* Loop */
    while (status == 0)
      {
        char *line = read_line("> ");
        status = eval(line);
        free(line);
      }

    /* Exit */
    exit_path();

    switch (status)
      {
        case 2: return 0;
        default: return status;
      }
  }
