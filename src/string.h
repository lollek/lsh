#ifndef LSH_STRING_H
#define LSH_STRING_H

/**
 * Split a sentence into separate words. E.g "Hello world" becomes
 * [0]: "Hello"
 * [1]: "World"
 * [2]: NULL
 *
 * When done, you should run freesplits() on the array
 */
char **splits(const char *cmd);

/**
 * Frees up the result of splits()
 */
void freesplits(char **sarray);

#endif /* LSH_STRING_H */
