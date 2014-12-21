#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "command.h"

static char **splits(const char *cmd)
  {
    char **retarray;
    int i;
    const char *cptr = cmd;
    int nsplits = 0;

    for (;;)
      {
        ++nsplits;
        cptr = strchr(cptr, ' ');
        if (cptr == NULL)
            break;
        cptr++;
      }

    retarray = malloc(sizeof *retarray * (nsplits + 1));
    if (retarray == NULL)
        return NULL;

    cptr = cmd;
    for (i = 0; i < nsplits; ++i)
      {
        char *newcptr = strchr(cptr, ' ');
        size_t ptrdiff;
        if (newcptr == NULL)
            ptrdiff = strlen(cptr);
        else
            ptrdiff = newcptr - cptr;
        retarray[i] = malloc(ptrdiff +1);

        if (retarray[i] == NULL)
          {
            while (--i >= 0)
                free(retarray[i]);
            free(retarray);
            return NULL;
          }

        strncpy(retarray[i], cptr, ptrdiff);
        retarray[i][ptrdiff] = '\0';
        cptr = newcptr + 1;
      }
    retarray[nsplits] = NULL;

    return retarray;
  }

static int help(void)
  {
    printf("Available commands:\n"
           "exit\t-\texit lsh\n"
          );
    return 0;
  }

static int tryexec(const char *argv)
  {
    char **args = splits(argv);
    size_t i;

    if (args == NULL)
      {
        fprintf(stderr, "Error %s L%d: splits(%s) == NULL!\n",
                __FILE__, __LINE__, argv);
        return 1;
      }

    if (!access(args[0], X_OK))
      {
        pid_t pid;
        switch(pid = fork())
          {
            case -1: perror("fork"); break;
            case 0: execv(args[0], args); break;
            default: waitpid(pid, NULL, 0); break;
          }
      }
    else
        perror("access");

    for (i = 0; args[i] != NULL; ++i)
        free(args[i]);
    free(args);

    return 0;
  }

int eval(const char *cmd)
  {
    if (!strcmp(cmd, "help"))
        return help();
    else if (!strcmp(cmd, "exit"))
        return 1;
    else
        return tryexec(cmd);
  }
