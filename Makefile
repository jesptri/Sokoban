_GUI = $(if $(NOGUI),,-D GUI -Werror)
_DEBUG = $(if $(DEBUG),-D DEBUG,)
_OPT = $(if $(OPT),-O3 -flto,)
CC = gcc
CFLAGS = -g -std=c99 -Wall $(_OPT) $(_GUI) $(_DEBUG) -I./include
LDFLAGS = -lSDL2

.PHONY: clean doc check-syntax compile-all launch-tests

# rule to generate the doxygen documentation
doc:
	doxygen conf/doxygen.conf

# rule to remove all .o files and all executables
clean:
	- rm -f *.o
	- find . -maxdepth 1 -executable -type f \( ! -name "Makefile" \) -delete

%.o: ./src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

%.o: ./tests/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

check-syntax: example-main.o read-file-formatted.o read-file-text.o \
	write-fact.o test-dummy.o sokoban.o loader.o test-loader.o test-move.o test-replay.o replay.o play.o linked_list_map.o

example-main: example-main.o
	$(CC) $(CFLAGS) -o example-main example-main.o

sokoban: sokoban.o replay.o loader.o
	$(CC) $(CFLAGS) -o sokoban sokoban.o replay.o loader.o

test-loader: test-loader.o loader.o sokoban.o
	$(CC) $(CFLAGS) -o test-loader test-loader.o loader.o sokoban.o

test-move:test-move.o sokoban.o loader.o
	$(CC) $(CFLAGS) -o test-move test-move.o sokoban.o loader.o

test-replay:test-replay.o sokoban.o loader.o
	$(CC) $(CFLAGS) -o test-replay test-replay.o sokoban.o loader.o

replay:replay.o loader.o sokoban.o
	$(CC) $(CFLAGS) -o replay replay.o loader.o sokoban.o

# linked_list_map:linked_list_map.o sokoban.o
# 	$(CC) $(CFLAGS) -o linked_list_map linked_list_map.o sokoban.o

test_linked_map:test_linked_map.o linked_list_map.o loader.o sokoban.o
	$(CC) $(CFLAGS) -o test_linked_map test_linked_map.o linked_list_map.o loader.o sokoban.o

play: play.o sokoban.o loader.o gui.o
	$(CC) $(CFLAGS) -o play play.o sokoban.o loader.o gui.o $(LDFLAGS)

example-string: example-string.o
	$(CC) $(CFLAGS) -o example-string example-string.o

read-file-formatted: read-file-formatted.o
	$(CC) $(CFLAGS) -o read-file-formatted read-file-formatted.o

read-file-text: read-file-text.o
	$(CC) $(CFLAGS) -o read-file-text read-file-text.o

write-fact: write-fact.o
	$(CC) $(CFLAGS) -o write-fact write-fact.o

test-dummy: test-dummy.o
	$(CC) $(CFLAGS) -o test-dummy test-dummy.o

# the app-ex-loader app
app-ex-loader: app-ex-loader.o
	$(CC) $(CFLAGS) -o app-ex-loader app-ex-loader.o

# the app-ex-gui app. Beware, for graphical applications, you MUST add $(LDFLAGS)!
app-ex-gui: app-ex-gui.o gui.o
	$(CC) $(CFLAGS) -o app-ex-gui app-ex-gui.o gui.o $(LDFLAGS)

# put all your applications and tests executables as prerequisite of this rule
# \ allows to go to the next line
compile-all: example-main read-file-formatted read-file-text \
	app-ex-loader \
	replay write-fact play test-dummy test-loader test-move test-replay

# add all your test executables in the following variable. You should respect
# the order given in the project text
# \ allows to go to the next line
ALL_TESTS = test-dummy test-loader test-move test-replay

launch-tests: $(ALL_TESTS)
	for x in $(ALL_TESTS); do ./$$x --all; done

# add all .c, .h and .txt files in repository
svn-add-all-files:
	svn add --force src/*.c include/*.h data/*.txt --auto-props --parents --depth infinity -q
