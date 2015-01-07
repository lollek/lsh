#include <stdlib.h>
#include "../libprompt/src/prompt.h"

#include "signal.h"
#include "command.h"
#include "command/path.h"

int
main(void)
  {
    int status = 0;

    /* Init */
    init_signals();

    /* Load config */
    command_path_init(NULL);

    /* Loop */
    while (status == 0)
      {
        char *line = prompt(". ");
        status = eval(line);
        free(line);
      }

    /* Exit */
    command_path_exit();

    switch (status)
      {
        case 2: return 0;
        default: return status;
      }
  }
