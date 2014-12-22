#ifndef LSH_COMMAND_H
#define LSH_COMMAND_H

/**
 * Evaluate cmd as a command
 * @param cmd String to evaluate
 * @return
 *  0 - success
 *  1 - error
 *  2 - user wants to exit
 */
int
eval(const char *cmd);

#endif /* LSH_COMMAND_H */
