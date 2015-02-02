#ifndef LSH_ARGPARSE_H
#define LSH_ARGPARSE_H

/**
 * argparse - Parse startup arguments
 * @argv	Null-terminated list of arguments to parse
 *
 * Returns:
 * -1		Success, continue with application
 *  *		Exit with returned value
 *
 * Description:
 * Created to parse &argv[1]+ from main()
 * If argv is NULL, or does not end with a NULL, this function will segfault
 */
int
argparse(char *argv[]);

#endif /* LSH_ARGPARSE_H */
