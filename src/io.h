#ifndef LSH_IO_H
#define LSH_IO_H

/**
 * stdout/err_set - Point stdout/stderr to a file
 * @file	File to redirect stdout to
 *
 * Returns:
 * 0		Success
 * 1		Error
 *
 */
int stdout_set(const char *file);
int stderr_set(const char *file);

/**
 * stdout/err_reset - Restore stdout/stderr to terminal
 */
void stdout_reset(void);
void stderr_reset(void);

#endif /* LSH_IO_H */

