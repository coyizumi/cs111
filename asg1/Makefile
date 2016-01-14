# A basic Makefile.
# Makes use of implicit rules for compiling C source code.
# exec defines the executable name
# OBJECTS defines the created object files (an implicit rule creates these from .c files)
# CFLAGS defines the flags used by the C compiler.
# CC defines the C compiler to use
# make all or make with no arguments will create the executable file
# make clean will remove any generated object files
# make spotless will remove object files and the executable file

exec    = myshell
OBJECTS = lex.yy.o myshell.o
CSOURCE = lex.yy.c myshell.c
CFLAGS  = -Wall -std=gnu11
LDLIBS  = -lfl
CC      = cc

LEX     = flex
LEXGEN  = lex.yy.c

all: $(exec)

$(exec): $(CSOURCE)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

lex.yy.c: lex.l
	$(LEX) -o $@ $^

clean:
	- rm $(OBJECTS)
	- rm $(LEXGEN)

spotless: clean
	- rm $(exec)
