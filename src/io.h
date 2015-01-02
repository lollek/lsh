#ifndef LSH_IO_H
#define LSH_IO_H

/**
 *  stdin_set - Redirect a stream
 * stdout_set
 * stderr_set
 * @file	File to redirect stdout to
 *
 * Returns:
 * 0		Success
 * 1		Error
 *
 */
int  stdin_set(const char *file);
int stdout_set(const char *file);
int stderr_set(const char *file);

/**
 *  stdin_reset - Restore stream to terminal
 * stdout_reset
 * stderr_reset
 */
void  stdin_reset(void);
void stdout_reset(void);
void stderr_reset(void);

#endif /* LSH_IO_H */

