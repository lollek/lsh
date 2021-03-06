#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "string.h"

char *
joins(char * const *cmds, const char *delim)
  {
    char *retval;
    char *retvalptr;
    size_t retvallen = 1;
    size_t delimlen = strlen(delim);
    int i;

    if (cmds[0] == NULL)
        return NULL;

    retvallen += strlen(cmds[0]);
    for (i = 1; cmds[i] != NULL; ++i)
        retvallen += delimlen + strlen(cmds[i]);

    retvalptr = retval = malloc(retvallen);
    if (retval == NULL)
        return NULL;

    retvalptr += sprintf(retvalptr, "%s", cmds[0]);
    for (i = 1; cmds[i] != NULL; ++i)
        retvalptr += sprintf(retvalptr, "%s%s", delim, cmds[i]);
    return retval;
  }

char **
splits(const char *cmd, const char *delim)
  {
    const size_t delimlen = strlen(delim);
    char **retarray;
    int i;
    const char *cptr;
    int nsplits = 1;

    if (cmd == NULL)
        return NULL;

    /* lstrip() */
    while (!strncmp(cmd, delim, delimlen))
        cmd += delimlen;

    /* Count nsplits */
    for (cptr = strstr(cmd, delim); cptr != NULL; cptr = strstr(cptr + delimlen, delim))
        ++nsplits;

    /* Allocate retarray */
    retarray = malloc(sizeof *retarray * (nsplits + 1));
    if (retarray == NULL)
        return NULL;

    /* Populate retarray[0 -> nsplits -1] */
    cptr = cmd;
    for (i = 0; i < nsplits; ++i)
      {
        char *newcptr = strstr(cptr, delim);
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
        if (newcptr == NULL)
            break;
        cptr = newcptr + delimlen;
      }
    retarray[nsplits] = NULL;

    return retarray;
  }

void
freesplits(char **sarray)
  {
    int i;
    for (i = 0; sarray[i] != NULL; ++i)
        free(sarray[i]);
    free(sarray);
  }
