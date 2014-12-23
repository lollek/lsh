#define BUFSIZ 256

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lineread.h"

char
*read_line(const char *prompt)
  {
    char buf[BUFSIZ];
    size_t retstrsiz = 1; /* room for null terminator */
    char *retstr = NULL;

    printf("%s", prompt);

    /* Add buf to retstr */
    while (fgets(buf, BUFSIZ, stdin) != NULL)
      {
        char *newretstr;
        size_t pos = retstrsiz;
        retstrsiz += strlen(buf);

        newretstr = realloc(retstr, retstrsiz);
        if (newretstr == NULL)
          {
            perror("read_line");
            free(retstr);
            return NULL;
          }
        retstr = newretstr;
        strcpy(retstr + pos -1, buf);

        if (retstr[retstrsiz -2] == '\n')
          {
            retstr[retstrsiz -2] = '\0';
            return retstr;
          }
      }

    return retstr;
  }
