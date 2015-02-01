#ifndef LSH_COMMAND_ALIAS_H
#define LSH_COMMAND_ALIAS_H

/**
 * command_alias - add or list alias(es)
 * @argv	like argv for a main() function
 *
 * Description;
 * If argv[1] is NULL, all aliases are displayed
 * If argv[2] is NULL, the alias for arg[1] is displayed
 * Otherwise, it sets an alias for argv[1] to be replaced with argv[2+]
 * Returns 0 on success
 */
int
command_alias(char * const *argv);

/**
 * command_alias_remove - remove alias(es)
 * @argv	like argv for a main() function
 *
 * Description;
 * Removes any alias set for argv[1] and forward
 * Returns 0 on success
 */
int
command_alias_remove(char * const *argv);

/**
 * command_alias_replace - replace alias with its command
 * @cmd		string in which to replace alias
 * @delim	delimiter used in string
 *
 * Description;
 * Checks if the part between cmd[0] and the start of the delimiter is an alias,
 * if it is, the string is replaced with the expanded command.
 *
 * The returned string must be freed when no longer needed IF the returned
 * string is not actually @cmd.
 */
char *
command_alias_replace(char *cmd, const char *delim);

#endif /* LSH_COMMAND_ALIAS_H */
