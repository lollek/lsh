#include <signal.h>
#include <stdio.h>

#include "signal.h"

void
send_newline(int signal)
  {
    (void)signal;
    putc('\n', stdin);
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
