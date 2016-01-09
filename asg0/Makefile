exec = cat
OBJECTS = cat.o 
CFLAGS = -Wall -std=gnu11
CC = cc

all: $(exec)

$(exec): $(OBJECTS)

clean:
	- rm $(OBJECTS)

spotless: clean
	- rm $(exec)