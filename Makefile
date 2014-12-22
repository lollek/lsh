CFLAGS=-Wall -Wextra -Werror -pedantic -std=c89 -O3 -g

LINT=cppcheck
LINTFLAGS=--std=c89 --enable=all

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
