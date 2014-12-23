#ifndef LSH_COMMAND_CD_H
#define LSH_COMMAND_CD_H

/**
 * command_cd - change directory
 * @argv	like argv for a main() function
 *
 * Description;
 * Change working directory to given path. If no path is given, directory is
 * changed to user's home directory.
 */
int
command_cd(char * const *argv);

#endif /* LSH_COMMAND_CD_H */
