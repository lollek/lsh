#ifndef LSH_LINEREAD_H
#define LSH_LINEREAD_H

/**
 * read_line - Read a line from stdin
 * @prompt	Prompt to print before reading a line
 *
 * Returns:
 *  string	On success
 *  NULL	On error or no input
 *
 * Description:
 * Reads and returns a line from the user, which should be freed after use.
 * Return value is NULL on errors or no input
 */
char *
read_line(const char *prompt);

#endif /* LSH_LINEREAD_H */
