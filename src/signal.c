#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "signal.h"

void
send_newline(int signal, siginfo_t *info, void *unused)
  {
    const pid_t this_process = 0;
    (void)signal;
    (void)unused;
    if (info->si_pid == this_process)
      write(STDIN_FILENO, "\n", 1);
    else
      exit(1);
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
