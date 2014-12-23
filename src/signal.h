#ifndef LSH_SIGNAL_H
#define LSH_SIGNAL_H

#include <signal.h>

/**
 * handle_sigint - Handle sigint signals to process
 *
 * Description:
 * This functions checks if the sender is the same function, if it is,
 * a newline is sent to stdin. Otherwise, the signal is treated normally.
 */
void
handle_sigint(int signal, siginfo_t *info, void *unused);

/**
 * init_signals - Set up signal handling
 */
int
init_signals(void);

#endif /* LSH_SIGNAL_H */
