.PHONY: all clean test

CC=gcc
CFLAGS=-std=c99 -Wall -fPIC -pthread -pedantic -D_XOPEN_SOURCE=600
DEBUGFLAGS=-ggdb
LIBS=-lm
C_FILES := $(wildcard src/*.c)
O_FILES := $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))

all : tetris libtetris.a

obj/%.o: src/%.c obj
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c -o $@ $<

obj:
	mkdir $@

tetris : $(O_FILES)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ $^ $(LIBS)

#tetris.o : src/tetris.c
#	$(CC) -c $(CFAGS) -o $@ $< $(LIBS)

libtetris.a : obj/tetris.o
	ar rcs $@ $<

# TODO figure out how to auto compile test files
# TODO Also figure out how to put shader files in own directory

clean: obj
	-rm obj/*.o
	-rm libtetris.a
	-rm tetris
