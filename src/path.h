#ifndef LSH_PATH_H
#define LSH_PATH_H

#ifndef DEFAULT_PATH
#define DEFAULT_PATH "/usr/local/bin:/usr/bin:/bin"
#endif /* DEFAULT_PATH */

/**
 * init_path - initialize the global path variable
 *
 * Returns:
 *  0		On success
 *
 * Description:
 * Init path to a default value, which is the DEFAULT_PATH above.
 * Path is used like $PATH in bash, i.e. contains folders in which
 * to look for files to execute.
 */
int
init_path(void);

/**
 * get_path - return a pointer to the global path variable
 */
char *
get_path(void);

/**
 * exit_path - Free global path variable
 */
void
exit_path(void);

#endif /* LSH_PATH_H */
