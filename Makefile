## Configurables:
# Prefix where to place library and header.
PREFIX=/usr/local

PROGNAME=lsh
VERSION=0.0.1

CFLAGS=-Wall -Wextra -Werror -pedantic -O3
CFLAGS+= -DPROGNAME=\"$(PROGNAME)\"
CFLAGS+= -DVERSION=\"$(VERSION)\"
LDFLAGS=

LINT=cppcheck
LINTFLAGS=--enable=all

HEADERS=$(wildcard src/*.h src/**/*.h)
SRCFILES=$(wildcard src/*.c src/**/*.c)
OBJFILES=$(addsuffix .o,$(basename $(SRCFILES)))

LIBOBJS=$(wildcard libprompt/src/*.o)

lsh:	$(OBJFILES) libs
	$(CC) $(LDFLAGS) -o $@ $(OBJFILES) $(LIBOBJS)

install: $(PROGNAME)
	cp $(PROGNAME) $(PREFIX)/bin/$(PROGNAME)
	chmod 0755 $(PREFIX)/bin/$(PROGNAME)
.PHONY: install

debug:	CFLAGS+= -g
debug: lsh

libs:
	make -C libprompt
.PHONY: libs

lint:
	$(LINT) $(LINTFLAGS) $(SRCFILES) $(HEADERS)
.PHONY: lint

clean:
	make clean -C libprompt
	$(RM) lsh $(OBJFILES)
.PHONY: clean
