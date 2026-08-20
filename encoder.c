// Brainfuck encoder in C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Sarxzer's Brainfuck Encoder\n");
        printf("Usage: %s <filename.bf>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");

    if (fp==NULL) {
        printf("Couldn't open file\n");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = malloc(size + 1);
    if (buffer == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    fread(buffer, 1, size, fp);
    buffer[size] = '\0';

    fclose(fp);

    int character = 0;

    for (long i = 0; i < size; i++) {
        // printf("%c", buffer[i]);

        character = buffer[i];
        
        for (int j = 0; j < character; j++) {
            putchar('+');
        }

        putchar('.');
        putchar('>');
    }
    putchar('\n');
    free(buffer);
    return 0;
}