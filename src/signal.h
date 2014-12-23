#ifndef LSH_SIGNAL_H
#define LSH_SIGNAL_H

#include <signal.h>

/**
 * send_newline - Signal handler to send a newline or exit
 *
 * Description:
 * This functions checks if the sender is the same function, if it is,
 * a newline is sent to stdin. If the sender is another process exit is executed
 * instead
 */
void
send_newline(int signal, siginfo_t *info, void *unused);

/**
 * init_signals - Set up signal handling
 */
int
init_signals(void);

#endif /* LSH_SIGNAL_H */
