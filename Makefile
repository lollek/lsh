CFLAGS=-Wall -Wextra -Werror -pedantic -std=c89 -O3 -g

SRCFILES=$(wildcard src/*.c)
OBJFILES=$(addsuffix .o,$(basename $(SRCFILES)))

lsh:	$(OBJFILES)
	$(CC) -o $@ $^

clean:
	$(RM) lsh $(OBJFILES)

.PHONY:	clean
