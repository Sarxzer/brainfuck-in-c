CC = gcc
CFLAGS = -Wall -Wextra -g

brainfuck: main.c
	$(CC) $(CFLAGS) main.c -o brainfuck

clean:
	rm -f brainfuck

run: main
	./brainfuck test.bf