#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAPE_SIZE 30000

char* executeBrainfuck(const char *code) {
    char tape[TAPE_SIZE] = {0};
    char *ptr = tape;
    const char *pc = code;
    char *output_buffer = (char*)malloc(TAPE_SIZE);
    if (!output_buffer) {
        perror("Failed to allocate memory for output buffer");
        exit(EXIT_FAILURE);
    }
    memset(output_buffer, 0, TAPE_SIZE);
    int output_index = 0;

    while (*pc) {
        switch (*pc) {
            case '>':
                ptr++;
                break;
            case '<':
                ptr--;
                break;
            case '+':
                (*ptr)++;
                break;
            case '-':
                (*ptr)--;
                break;
            case '.':
                output_buffer[output_index++] = *ptr;  // Save output to buffer
                break;
            case ',':
                *ptr = getchar();
                break;
            case '[':
                if (*ptr == 0) {
                    int loop = 1;
                    while (loop > 0) {
                        pc++;
                        if (*pc == '[') loop++;
                        if (*pc == ']') loop--;
                    }
                }
                break;
            case ']':
                if (*ptr != 0) {
                    int loop = 1;
                    while (loop > 0) {
                        pc--;
                        if (*pc == '[') loop--;
                        if (*pc == ']') loop++;
                    }
                }
                break;
        }
        pc++;
    }

    return output_buffer;
}

void readAndExecuteFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *code = (char*)malloc(length + 1);
    if (!code) {
        perror("Failed to allocate memory for code");
        exit(EXIT_FAILURE);
    }

    fread(code, 1, length, file);
    code[length] = '\0';

    fclose(file);

    char* output = executeBrainfuck(code);
    printf("%s", output);
    free(output);
    free(code);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    readAndExecuteFile(argv[1]);

    return EXIT_SUCCESS;
}
