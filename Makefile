CFLAGS=-Wall -Wextra -Werror -pedantic -O3 -g

LINT=cppcheck
LINTFLAGS=--enable=all

HEADERS=$(wildcard src/*.h)
SRCFILES=$(wildcard src/*.c)
OBJFILES=$(addsuffix .o,$(basename $(SRCFILES)))

lsh:	$(OBJFILES)
	$(CC) -o $@ $^

lint:
	$(LINT) $(LINTFLAGS) $(SRCFILES) $(HEADERS)

clean:
	$(RM) lsh $(OBJFILES)

.PHONY:	clean lint
