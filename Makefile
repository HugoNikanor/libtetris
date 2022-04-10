.PHONY: all clean test

LIBS=sdl2
CFLAGS=-std=c99 -Wall -fPIC -pthread -pedantic -D_XOPEN_SOURCE=600 \
	   $(shell pkg-config --cflags $(LIBS))
DEBUGFLAGS=-ggdb
LDLIBS=-lm $(shell pkg-config --libs $(LIBS))
C_FILES := $(wildcard src/*.c)
# O_FILES := $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))

all : tetris sdl_tetris libtetris.a libtetris.so

obj/%.o: src/%.c
	-@mkdir -p obj
	$(CC) -c $(CFLAGS) $(DEBUGFLAGS) -o $@ $<


tetris: obj/main.o obj/graphics.o obj/tetris.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

sdl_tetris: obj/sdl_main.o obj/graphics.o obj/tetris.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

libtetris.so: obj/tetris.o
	$(CC) $^ -shared -o $@ $(LDLIBS)

libtetris.a : obj/tetris.o
	ar rcs $@ $^

# TODO figure out how to auto compile test files
# TODO Also figure out how to put "shader" files in own directory

clean:
	-rm obj/*.o
	-rmdir obj
	-rm libtetris.a
	-rm libtetris.so
	-rm tetris
