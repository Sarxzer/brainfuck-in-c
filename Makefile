CC = gcc
CFLAGS = -Wall -Wextra -g

WIN_CC = x86_64-w64-mingw32-gcc
WIN_CFLAGS = -Wall -Wextra -O2

brainfuck: main.c
	$(CC) $(CFLAGS) main.c -o brainfuck

windows: main.c
	$(WIN_CC) $(WIN_CFLAGS) main.c -o brainfuck.exe

clean:
	rm -f brainfuck

run: brainfuck
	./brainfuck ./examples/beurreland.bf