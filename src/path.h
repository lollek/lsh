#ifndef LSH_PATH_H
#define LSH_PATH_H

#ifndef DEFAULT_PATH
#define DEFAULT_PATH "/usr/local/bin:/usr/bin:/bin"
#endif /* DEFAULT_PATH */

/**
 * Init path to a default value, which is the DEFAULT_PATH above.
 * Path is used like $PATH in bash, i.e. contains folders in which
 * to look for files to execute.
 * @return 0 on success
 */
int
init_path(void);

/**
 * Get a pointer to the path string
 */
char *
get_path(void);

/**
 * Free path
 */
void
exit_path(void);

#endif /* LSH_PATH_H */
