#ifndef LSH_COMMAND_H
#define LSH_COMMAND_H

/**
 * eval - Evaluate a string
 * @cmd		String to evaluate
 *
 * Returns:
 *  0		Success
 *  1		Error
 *  2		User wants to exit
 *
 * Description:
 * Evaluate (and execute) a command and return
 */
int
eval(char *cmd);

/**
 * exec_file - execute a file
 * @file	File to parse
 *
 * Returns:
 *  0		Success
 *  1		Error
 *
 * Description:
 * Parse and execute a file instead of standard input
 */
int
exec_file(const char *file);

#endif /* LSH_COMMAND_H */
