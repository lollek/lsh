#ifndef LSH_STRING_H
#define LSH_STRING_H

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
 * E.g splits("Hello world", ' ') returns sarray where
 * sarray[0] = "Hello"
 * sarray[1] = "World"
 * sarray[2] = NULL
 *
 * When done, you should run freesplits() on the array
 */
char **
splits(const char *cmd, int delim);

/**
 * freesplits - Frees up the result of splits()
 */
void
freesplits(char **sarray);

#endif /* LSH_STRING_H */
