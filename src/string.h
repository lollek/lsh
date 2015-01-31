#ifndef LSH_STRING_H
#define LSH_STRING_H

/**
 * joins - Reverses the effect of splits
 * @cmds	Array of split strings
 * @delim	Delimiter to join the strings with
 *
 * Returns:
 *  strings	On success
 *  NULL	If malloc fails
 *
 * Description:
 * Reverses the effect of splits
 *
 * When done, you should need to free the returned string
 */
char *
joins(char * const *cmd, const char *delim);

/**
 * splits - Split a sentence into separate words.
 * @cmd		String to split
 * @delim	Delimiter to split on
 *
 * Returns:
 *  strings	On success
 *  NULL	If malloc fails
 *
 * Description:
 * Split a string into an array of words, which is NULL-terminated.
 * E.g splits("  Hello world  ", " ") returns sarray where
 * sarray[0] = "Hello"
 * sarray[1] = "World"
 * sarray[2] = NULL
 *
 * When done, you should run freesplits() on the array
 */
char **
splits(const char *cmd, const char *delim);

/**
 * freesplits - Frees up the result of splits()
 */
void
freesplits(char **sarray);

#endif /* LSH_STRING_H */
