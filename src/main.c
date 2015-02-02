#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../libprompt/src/prompt.h"

#include "argparse.h"
#include "signal.h"
#include "command.h"
#include "command/path.h"

int
main(int argc, char *argv[])
  {
    int status = 0;
    (void)argc;

    /* Init */
    init_signals();
    command_path_init(NULL);

    /* Parse arguments */
    status = argparse(&argv[1]);
    if (status != -1)
        return status;

    /* Loop */
    do
      {
        char *line = prompt(". ");
        status = eval(line);
        free(line);
      }
    while (status == 0);

    /* Exit */
    command_path_exit();

    switch (status)
      {
        case 2: return 0;
        default: return status;
      }
  }
