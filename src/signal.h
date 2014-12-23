#ifndef LSH_SIGNAL_H
#define LSH_SIGNAL_H

/**
 * handle_sigint - Handle sigint signals to process
 *
 * Description:
 * This functions currently does nothing.
 */
void
handle_sigint(int signal);

/**
 * init_signals - Set up signal handling
 */
int
init_signals(void);

#endif /* LSH_SIGNAL_H */
