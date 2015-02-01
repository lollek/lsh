#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../libprompt/src/prompt.h"

#include "signal.h"
#include "command.h"
#include "command/path.h"

static int
argparse(char *argv[])
  {
    char *arg = argv[0];
    char **next = &argv[1];

    if (arg[0] != '-')
        exit(exec_file(arg));
    else if (!strcmp(arg, "--version"))
      {
        puts(PROGNAME " version " VERSION);
        exit(0);
      }

    else if (!strcmp(arg, "--help"))
      {
        printf("Usage: " PROGNAME " [options] [FILE]\n"
              " --help             Print this help and exit\n"
              " --version          Print version and exit\n"
              );
        exit(0);
      }
    else
      {
        fprintf(stderr, PROGNAME ": Unknown argument: '%s'\n", arg);
        exit(1);
      }

    return *next ? argparse(next) : 0;
  }

int
main(int argc, char *argv[])
  {
    int status = 0;

    /* Init */
    init_signals();
    command_path_init(NULL);

    if (argc > 1)
      argparse(&argv[1]);

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
