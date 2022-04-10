.PHONY: all clean test

CC=gcc
CFLAGS=-std=c99 -Wall -fPIC -pthread -pedantic -D_XOPEN_SOURCE=600
DEBUGFLAGS=-ggdb
LIBS=-lm
C_FILES := $(wildcard src/*.c)
O_FILES := $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))

obj/%.o: src/%.c
	$(CC) -c $(CFLAGS) $(DEBUGFLAGS) -o $@ $<

tetris : $(O_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

libtetris.so: obj/tetris.o
	$(CC) $^ -shared -o $@

libtetris.a : obj/tetris.o
	ar rcs libtetris.a tetris.o

all : tetris libtetris.a libtetris.so

# TODO figure out how to auto compile test files
# TODO Also figure out how to put "shader" files in own directory

clean:
	-rm obj/*.o
	-rm test/*.o
