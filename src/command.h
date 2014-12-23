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
eval(const char *cmd);

#endif /* LSH_COMMAND_H */
