#ifndef LSH_IO_H
#define LSH_IO_H

/**
 * stdout_set - Point stdout to a file
 * @file	File to redirect stdout to
 *
 * Returns:
 * 0		Success
 * 1		Error
 *
 */
int stdout_set(const char *file);

/**
 * stdout_reset - Restore stdout to terminal
 */
void stdout_reset(void);

#endif /* LSH_IO_H */

