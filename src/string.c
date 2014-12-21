#include <stdlib.h>
#include <string.h>

#include "string.h"

char **
splits(const char *cmd)
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

void freesplits(char **sarray)
  {
    int i;
    for (i = 0; sarray[i] != NULL; ++i)
        free(sarray[i]);
    free(sarray);
  }
