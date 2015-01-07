CFLAGS=-Wall -Wextra -Werror -pedantic -O3
LDFLAGS=

LINT=cppcheck
LINTFLAGS=--enable=all

HEADERS=$(wildcard src/*.h src/**/*.h)
SRCFILES=$(wildcard src/*.c src/**/*.c)
OBJFILES=$(addsuffix .o,$(basename $(SRCFILES)))

LIBOBJS=$(wildcard libprompt/src/*.o)

lsh:	$(OBJFILES) libs
	$(CC) $(LDFLAGS) -o $@ $(OBJFILES) $(LIBOBJS)

debug:	CFLAGS+= -g
debug: lsh

libs:
	make -C libprompt

lint:
	$(LINT) $(LINTFLAGS) $(SRCFILES) $(HEADERS)

clean:
	make clean -C libprompt
	$(RM) lsh $(OBJFILES)

.PHONY:	clean lint libs
