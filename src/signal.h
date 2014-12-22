#ifndef LSH_SIGNAL_H
#define LSH_SIGNAL_H

#include <signal.h>

void
send_newline(int signal, siginfo_t *info, void *unused);

int
init_signals(void);

#endif /* LSH_SIGNAL_H */
