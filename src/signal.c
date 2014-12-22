#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "signal.h"

void
send_newline(int signal, siginfo_t *info, void *unused)
  {
    (void)signal;
    (void)unused;
    if (info->si_pid == 0) /* Send by this program */
      write(STDIN_FILENO, "\n", 1);
    else
      exit(0);
  }

int
init_signals(void)
  {
    struct sigaction action;
    action.sa_sigaction = send_newline;
    action.sa_flags = SA_SIGINFO;
    sigemptyset(&action.sa_mask);

    if (sigaction(SIGINT, &action, NULL) != 0)
      {
        perror("sigaction");
        return 1;
      }
    return 0;
  }
