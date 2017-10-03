.PHONY: all clean test

CC=gcc
CFLAGS=-std=c99 -Wall -fPIC -pedantic -D_XOPEN_SOURCE=600
DEBUGFLAGS=-ggdb
LIBS=-lm
C_FILES := $(wildcard src/*.c)
O_FILES := $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

tetris : $(O_FILES)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ $^ $(LIBS)

all : tetris

# TODO figure out how to auto compile test files
# TODO Also figure out how to put shader files in own directory

clean:
	-rm obj/*.o
	-rm test/*.o
