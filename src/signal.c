#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include "signal.h"

void
send_newline(int signal)
  {
    (void)signal;
    write(STDIN_FILENO, "\n", 1);
  }

int
init_signals(void)
  {
    struct sigaction action;
    action.sa_handler = send_newline;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);

    if (sigaction(SIGINT, &action, NULL) != 0)
      {
        perror("sigaction");
        return 1;
      }
    return 0;
  }
