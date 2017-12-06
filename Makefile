.PHONY: all clean test

CC=gcc
CFLAGS=-std=c99 -Wall -fPIC -pthread -pedantic -D_XOPEN_SOURCE=600
DEBUGFLAGS=-ggdb
LIBS=-lm
C_FILES := $(wildcard src/*.c)
O_FILES := $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))

obj/%.o: src/%.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c -o $@ $<

tetris : $(O_FILES)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ $^ $(LIBS)

tetris.o : src/tetris.c
	$(CC) -c $(CFAGS) -o $@ $< $(LIBS)

libtetris.a : tetris.o
	ar rcs libtetris.a tetris.o

all : tetris libtetris.a

# TODO figure out how to auto compile test files
# TODO Also figure out how to put shader files in own directory

clean:
	-rm obj/*.o
	-rm test/*.o
