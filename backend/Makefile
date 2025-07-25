_GUI = $(if $(NOGUI),,-DGUI -Werror)
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
# clean:
# 	- rm -f *.o
# 	- find . -maxdepth 1 -executable -type f \( ! -name "Makefile" \) -delete

clean:
	- rm -f *.o
	- find . -maxdepth 1 -type f ! -name "*.*" ! -name "Makefile" ! -name "README" -exec rm {} +


%.o: ./src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

%.o: ./tests/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

check-syntax: example-main.o read-file-formatted.o read-file-text.o \
	write-fact.o test-dummy.o sokoban.o loader.o test-loader.o test-move.o test-replay.o test-solver.o replay.o play.o linked_list_map.o queue_map.o solver.o

example-main: example-main.o
	$(CC) $(CFLAGS) -o example-main example-main.o

### HELPER FILES ###



### FILES ###

sokoban: sokoban.o replay.o loader.o
	$(CC) $(CFLAGS) -o sokoban sokoban.o replay.o loader.o

play: play.o loader.o sokoban.o
	$(CC) $(CFLAGS) -o play play.o loader.o sokoban.o

replay:replay.o loader.o sokoban.o
	$(CC) $(CFLAGS) -o replay replay.o loader.o sokoban.o

play_step: src/play_step.o loader.o sokoban.o
	$(CC) $(CFLAGS) -o play_step src/play_step.o loader.o sokoban.o

solve: solve.o sokoban.o solver.o loader.o linked_list_map.o queue_map.o
	$(CC) $(CFLAGS) -o solve solve.o sokoban.o solver.o loader.o linked_list_map.o queue_map.o

### TESTS ###

test-loader: test-loader.o loader.o sokoban.o
	$(CC) $(CFLAGS) -o test-loader test-loader.o loader.o sokoban.o

test-move:test-move.o sokoban.o loader.o
	$(CC) $(CFLAGS) -o test-move test-move.o sokoban.o loader.o

test-replay:test-replay.o sokoban.o loader.o
	$(CC) $(CFLAGS) -o test-replay test-replay.o sokoban.o loader.o

test_linked_list_map:test_linked_list_map.o linked_list_map.o loader.o sokoban.o solver.o queue_map.o
	$(CC) $(CFLAGS) -o test_linked_list_map test_linked_list_map.o linked_list_map.o loader.o sokoban.o solver.o queue_map.o

test_queue_map:test_queue_map.o queue_map.o loader.o sokoban.o
	$(CC) $(CFLAGS) -o test_queue_map test_queue_map.o queue_map.o loader.o sokoban.o

test-solver:test-solver.o solver.o loader.o sokoban.o linked_list_map.o queue_map.o
	$(CC) $(CFLAGS) -o test-solver test-solver.o solver.o loader.o sokoban.o linked_list_map.o queue_map.o

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
app-ex-gui: app-ex-gui.o gui.o loader.o sokoban.o
	$(CC) $(CFLAGS) -o app-ex-gui app-ex-gui.o gui.o loader.o sokoban.o $(LDFLAGS)

# put all your applications and tests executables as prerequisite of this rule
# \ allows to go to the next line
compile-all: app-ex-gui app-ex-loader example-main read-file-formatted read-file-text write-fact \
	sokoban play replay solve \
	test-dummy test-loader test-move test-replay test_linked_list_map test_queue_map test-solver

# add all your test executables in the following variable. You should respect
# the order given in the project text
# \ allows to go to the next line
ALL_TESTS = test-dummy test-loader test-move test-replay

launch-tests: $(ALL_TESTS)
	for x in $(ALL_TESTS); do ./$$x --all; done

# add all .c, .h and .txt files in repository
svn-add-all-files:
	svn add --force src/*.c include/*.h data/*.txt --auto-props --parents --depth infinity -q
