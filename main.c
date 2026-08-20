// Brainfuck interpreter in C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc >= 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        printf("Sarxzer's Brainfuck Interpreter\n");
        printf("Usage: %s <filename.bf>\n", argv[0]);
        printf("       %s -t \"<brainfuck code>\"\n", argv[0]);
        return 1;
    }
    int pointer = 0;
    unsigned char tape [30000];
    int ipointer;

    memset(tape, 0, sizeof(tape));

    long size;
    char *buffer;

    if (argc >= 2 && strcmp(argv[1], "-t") == 0) {
        if (argc < 3) {
            printf("Please provide code after -t\n");
            return 1;
        }
        size = strlen(argv[2]);

        buffer = malloc(size + 1);
        if (buffer == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        strcpy(buffer, argv[2]);

        buffer[size] = '\0';
    } else if (argc >= 2) {
        FILE *fp = fopen(argv[1], "r");

        if (fp==NULL) {
            printf("Couldn't open file\n");
            return 1;
        }

        fseek(fp, 0, SEEK_END);
        size = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        buffer = malloc(size + 1);
        if (buffer == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }

        fread(buffer, 1, size, fp);
        buffer[size] = '\0';

        fclose(fp);
    } else if (!isatty(fileno(stdin))) {
        long capacity = 1024;  // start smaller, we'll grow as needed
        buffer = malloc(capacity);
        if (buffer == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        size = 0;
        
        int ch;
        while ((ch = getchar()) != EOF) {
            if (size >= capacity) {
                capacity *= 2;
                buffer = realloc(buffer, capacity);
                if (buffer == NULL) {
                    printf("Memory allocation failed\n");
                    return 1;
                }
            }
            buffer[size] = ch;
            size++;
        }
        buffer[size] = '\0';
    } else {
        printf("Sarxzer's Brainfuck Interpreter\n");
        printf("Usage: %s <filename.bf>\n", argv[0]);
        printf("       %s -t \"<brainfuck code>\"\n", argv[0]);
        return 1;
    }

    // printf("%c\n", buffer[0]);

    int *jumptable = malloc(size * sizeof(int));
    int *stack = malloc(size * sizeof(int));
    int stack_top = 0;
    int i;
    int popped_index;

    for (i = 0; i < size; i++) {
        if (buffer[i] == '[') {
            //add i to stack
            stack[stack_top] = i;
            stack_top++;
        }
        if (buffer[i] == ']') {
            //pop from stack
            stack_top--;
            popped_index = stack[stack_top];
            jumptable[popped_index] = i;
            jumptable[i] = popped_index;
        }
    }

    free(stack);

    for (ipointer = 0; ipointer < size; ipointer++) {

        switch (buffer[ipointer])
        {
        case '>':
            pointer++;
            if (pointer >= 30000) {
                printf("Error: pointer out of bounds (too high)\n");
                return 1;
            }
            break;
        
        case '<':
            pointer--;
            if (pointer < 0) {
                printf("Error: pointer out of bounds (too low)\n");
                return 1;
            }
            break;
        
        case '+':
            tape[pointer]++;
            break;
        
        case '-':
            tape[pointer]--;
            break;

        case '.':
            printf("%c", tape[pointer]);
            break;
        
        case ',':
            tape[pointer] = getchar();
            break;
        
        case '[':
            if (tape[pointer] == 0) {
                ipointer = jumptable[ipointer];
            }
            break;
        
        case ']':
            if (tape[pointer] != 0) {
                ipointer = jumptable[ipointer];
            }
            break;
        
        default:
            break;
        }


        // printf("%c\n", buffer[ipointer]);
        // printf("pointer: %d\n", pointer);

    }

    // for (int i = 0; i < 10; i++) {
    //     printf("%d ", tape[i]);
    // }
    // printf("\n");

    free(buffer);
    free(jumptable);
    return 0;
}