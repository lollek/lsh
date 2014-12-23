#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "signal.h"

static struct sigaction origsigint;

void
handle_sigint(int signal, siginfo_t *info, void *unused)
  {
    const pid_t this_process = 0;
    if (info->si_pid == this_process)
        write(STDIN_FILENO, "\n", 1);
    else
        origsigint.sa_sigaction(signal, info, unused);
  }

int
init_signals(void)
  {
    struct sigaction action;
    action.sa_sigaction = handle_sigint;
    action.sa_flags = SA_SIGINFO;
    sigemptyset(&action.sa_mask);

    if (sigaction(SIGINT, &action, &origsigint) != 0)
      {
        perror("sigaction");
        return 1;
      }
    return 0;
  }
