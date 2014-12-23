CFLAGS=-Wall -Wextra -Werror -pedantic -O3 -g
LDFLAGS=-lreadline

LINT=cppcheck
LINTFLAGS=--enable=all

HEADERS=$(wildcard src/*.h src/**/*.h)
SRCFILES=$(wildcard src/*.c src/**/*.c)
OBJFILES=$(addsuffix .o,$(basename $(SRCFILES)))

lsh:	$(OBJFILES)
	$(CC) $(LDFLAGS) -o $@ $^

lint:
	$(LINT) $(LINTFLAGS) $(SRCFILES) $(HEADERS)

clean:
	$(RM) lsh $(OBJFILES)

.PHONY:	clean lint
