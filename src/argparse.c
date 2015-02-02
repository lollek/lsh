#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"

#include "argparse.h"

static int
version(void)
  {
    puts(PROGNAME " version " VERSION);
    return 0;
  }

static int
help(void)
  {
    printf("Usage: " PROGNAME " [options] [FILE]\n"
          " --help             Print this help and exit\n"
          " --version          Print version and exit\n"
          "\n"
          );
    return version();
  }

static int
unknown(char *arg)
  {
    fprintf(stderr, PROGNAME ": Unknown argument: '%s'\n", arg);
    return 1;
  }

int
argparse(char *argv[])
  {
    char **next;
    char *arg;

    if (argv == NULL || argv[0] == NULL)
        return -1;

    arg = argv[0];
    next = &argv[1];

    if (arg[0] != '-')                  return exec_file(arg);
    else if (!strcmp(arg, "--version")) return version();
    else if (!strcmp(arg, "--help"))    return help();
    else                                return unknown(arg);

    return *next ? argparse(next) : -1;
  }

