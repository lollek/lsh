#ifndef LSH_PATH_H
#define LSH_PATH_H

#ifndef DEFAULT_PATH
#define DEFAULT_PATH "/usr/local/bin:/usr/bin:/bin"
#endif /* DEFAULT_PATH */

/**
 * command_path_init - initialize the global path variable
 * @path	path to initialize, or NULL for DEFAULT_PATH
 *
 * Returns:
 *  0		On success
 *
 * Description:
 * Path is used like $PATH in bash, i.e. contains folders in which
 * to look for files to execute.
 */
int
command_path_init(const char *path);

/**
 * command_path_get - return a pointer to the global path variable
 */
char *
command_path_get(void);

/**
 * command_path_exit - Free global path variable
 */
void
command_path_exit(void);

char *
command_path_find(const char *path);

int
command_path(char **argv);

#endif /* LSH_PATH_H */
