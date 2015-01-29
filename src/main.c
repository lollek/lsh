#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../libprompt/src/prompt.h"

#include "signal.h"
#include "command.h"
#include "command/path.h"

int
argparse(char arg[])
  {
    if (!strcmp(arg, "--version"))
        puts(PROGNAME " version " VERSION);
    else if (!strcmp(arg, "--help"))
        printf("Usage: " PROGNAME " [options]\n"
              " --help             Print this help and exit\n"
              " --version          Print version and exit\n"
              );
    else
        return !!fprintf(stderr, PROGNAME ": Unknown argument: '%s'\n", arg);
    return 0;
  }

int
main(int argc, char *argv[])
  {
    int status = 0;

    if (--argc)
        return argparse(argv[argc]);

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
