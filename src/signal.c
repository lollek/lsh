#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include "signal.h"

void
handle_sigint(int signal)
  {
    (void)signal;
  }

int
init_signals(void)
  {
    struct sigaction action;
    action.sa_handler = handle_sigint;
    action.sa_flags = SA_SIGINFO;
    sigemptyset(&action.sa_mask);

    if (sigaction(SIGINT, &action, NULL) != 0)
      {
        perror("sigaction");
        return 1;
      }
    return 0;
  }
