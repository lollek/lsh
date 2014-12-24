#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


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
        char *line = readline("> ");
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
