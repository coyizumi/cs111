# A basic Makefile.
# Makes use of implicit rules for compiling C source code.
# exec defines the executable name
# OBJECTS defines the created object files (an implicit rule creates these from .c files)
# CFLAGS defines the flags used by the C compiler.
# CC defines the C compiler to use
# make all or make with no arguments will create the executable file
# make clean will remove any generated object files
# make spotless will remove object files and the executable file

exec    = cat
OBJECTS = cat.o 
CFLAGS  = -Wall -std=gnu11
CC      = cc

all: $(exec)

$(exec): $(OBJECTS)

clean:
	- rm $(OBJECTS)

spotless: clean
	- rm $(exec)
