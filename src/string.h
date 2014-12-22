#ifndef LSH_STRING_H
#define LSH_STRING_H

/**
 * Split a sentence into separate words.
 * E.g splits("Hello world", ' ') returns sarray where
 * sarray[0] = "Hello"
 * sarray[1] = "World"
 * sarray[2] = NULL
 *
 * NB: When done, you should run freesplits() on the array
 *
 * @param cmd The string to split
 * @param delim The string delimiter for splitting
 */
char **
splits(const char *cmd, int delim);

/**
 * Frees up the result of splits()
 * @param sarray Array returns from splits
 */
void
freesplits(char **sarray);

#endif /* LSH_STRING_H */
