CFLAGS=-Wall -Wextra -Werror -pedantic -O3

SRCFILES=$(wildcard src/*.c)
OBJFILES=$(addsuffix .o,$(basename $(SRCFILES)))

lsh:	$(OBJFILES)
	$(CC) -o $@ $^

clean:
	$(RM) lsh $(OBJFILES)

.PHONY:	clean
