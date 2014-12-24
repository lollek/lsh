#include <stdlib.h>
#include <string.h>

#include "string.h"

char **
splits(const char *cmd, int delim)
  {
    char **retarray;
    int i;
    const char *cptr;
    int nsplits = 0;

    if (cmd == NULL)
        return NULL;

    /* lstrip() */
    while (*cmd == delim)
        cmd++;

    /* Count nsplits */
    cptr = cmd;
    while (*cptr != '\0')
      {
        ++nsplits;
        cptr = strchr(cptr, delim);
        if (cptr == NULL)
            break;
        while (*cptr == delim)
            cptr++;
      }

    /* Allocate retarray */
    retarray = malloc(sizeof *retarray * (nsplits + 1));
    if (retarray == NULL)
        return NULL;

    /* Populate retarray[0 -> nsplits -1] */
    cptr = cmd;
    for (i = 0; i < nsplits; ++i)
      {
        char *newcptr = strchr(cptr, delim);
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
        cptr = newcptr;
        if (cptr == NULL)
            break;
        while (*cptr == delim)
            cptr++;
        if (cptr == NULL)
            break;
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
