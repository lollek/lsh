#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "../string.h"

#include "alias.h"

typedef struct alias_list
  {
    char *alias;
    char *command;
    struct alias_list *next;
  }
alias_list_t;

static alias_list_t *root = NULL;
static alias_list_t *tail = NULL;

int
command_alias_add(char * const *argv)
  {
    alias_list_t *tmptail;

    if (argv[1] == NULL)
      {
        alias_list_t *i;
        for (i = root; i != NULL; i = i->next)
            printf("\t%s: '%s\n", i->alias, i->command);
        return 0;
      }

    if (argv[2] == NULL)
      {
        alias_list_t *i;
        for (i = root; i != NULL; i = i->next)
            if (!strcmp(argv[1], i->alias))
                return !printf("alias: %s: '%s'\n", argv[1], i->command);
        return !!fprintf(stdout, "alias: %s: No such alias\n", argv[1]);
      }

    if (root == NULL)
      {
        root = malloc(sizeof *root);
        if (root == NULL)
            return 1;
        tmptail = root;
      }
    else
      {
        tail->next = malloc(sizeof *tail);
        if (tail->next == NULL)
            return 1;
        tmptail = tail->next;
      }

    tmptail->alias = malloc(strlen(argv[1]) +1);
    tmptail->command = joins(&argv[2], " $");

    if (tmptail->alias == NULL || tmptail->command == NULL)
      {
        free(tmptail->alias);
        free(tmptail->command);
        free(tmptail);
        if (tmptail == root)
            root = NULL;
        else
            tail->next = NULL;
        return 1;
      }

    strcpy(tmptail->alias, argv[1]);
    tmptail->next = NULL;
    tail = tmptail;

    return 0;
  }

int
command_alias_remove(char * const *argv)
  {
    alias_list_t *j = NULL;
    alias_list_t *i;

    while (*(++argv) != NULL)
      {
        bool alias_removed = false;
        for (i = root; i != NULL; j = i, i = i->next)
            if (!strcmp(i->alias, *argv))
              {
                if (j == NULL)
                    root = i->next;
                else
                    j->next = i->next;
                free(i->alias);
                free(i->command);
                free(i);
                alias_removed = true;
                break;
              }
        if (!alias_removed)
            fprintf(stderr, "alias: %s: No such alias\n", *argv);
      }

    return 1;
  }

char *
command_alias_replace(char *cmd, const char *delim)
  {
    alias_list_t *i;
    const char *cmdend = strstr(cmd, delim);
    size_t cmdlen = strlen(cmd);
    size_t argv0len = cmdend == NULL ? cmdlen : (size_t)(cmdend - cmd);

    for (i = root; i != NULL; i = i->next)
        if (!strncmp(cmd, i->alias, argv0len))
            {
              size_t commandlen = strlen(i->command);
              char *retval = malloc(cmdlen - argv0len + commandlen +1);
              if (retval == NULL)
                  return cmd;

              strcpy(retval, i->command);
              strcpy(retval + commandlen, cmd + argv0len);
              return retval;
            }
    return cmd;
  }
