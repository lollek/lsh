#ifndef LSH_LINEREAD_H
#define LSH_LINEREAD_H

/**
 * read_line - Read a line from stdin
 * @prompt:	prompt to print before reading a line
 *
 * Description:
 * Reads and returns a line from the user, which should be freed after use.
 * Return value is NULL on errors or no input
 */
char *
read_line(const char *prompt);

#endif /* LSH_LINEREAD_H */
