.PHONY: all clean test

CC=gcc
CFLAGS=-std=c99 -Wall -fPIC -pthread -pedantic -D_XOPEN_SOURCE=600
DEBUGFLAGS=-ggdb
LIBS=-lm
C_FILES := $(wildcard src/*.c)
O_FILES := $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))

all : tetris libtetris.a libtetris.so

include $(C_FILES:src/%.c=obj/%.d)

obj/%.o: src/%.c
	-@mkdir -p obj
	$(CC) -c $(CFLAGS) $(DEBUGFLAGS) -o $@ $<

# Sed stuff to replace '%.o: ...' with 'obj/%.o obj/%.d ...'
# See the GNU Makefile manual, Generating Prerequisites Automatically
obj/%.d: src/%.c
	-@mkdir -p obj
	@set -e; \
		rm -f $@; \
		$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,obj/\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

tetris : $(O_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

libtetris.so: obj/tetris.o
	$(CC) $^ -shared -o $@

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
