#include <iostream>
#include <vector>

#include "command.h"

#include "argparse.h"

static auto
version() -> int
  {
    std::cout
      << PROGNAME " version " VERSION
      << std::endl;
    return 0;
  }

static auto
help() -> int
  {
    std::cout
      << "Usage: " PROGNAME " [options] [FILE]\n"
      << " --help             Print this help and exit\n"
      << " --version          Print version and exit\n"
      << std::endl;
    return version();
  }

static auto
unknown(std::string& arg) -> int
  {
    std::cerr
      << PROGNAME ": Unknown argument: '" << arg << "'"
      << std::endl;
    return 1;
  }

static auto
argparse(std::vector<std::string>& args) -> int
  {
    for (auto &string : args)
      {
        if (string[0] != '-')           return exec_file(string.c_str());
        else if (string == "--version") return version();
        else if (string == "--help")    return help();
        else                            return unknown(string);
      }

    return -1;
  }

int
argparse(char *argv[], int argc)
  {
    if (argv == NULL || argv[0] == NULL)
        return -1;

    std::vector<std::string> args(argv, argv + argc);
    return argparse(args);
  }

