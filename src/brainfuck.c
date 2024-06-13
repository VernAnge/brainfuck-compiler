/**
 * Brainfuck Interpreter
 * 
 * This program implements an interpreter for the Brainfuck programming language.
 * The interpreter is implemented in C and consists of the following components:
 * 
 * 1. executeBrainfuck(const char *code): 
 *    - This function takes Brainfuck code as input and executes it.
 *    - It uses a tape of size 30,000 cells (initialized to zero) to store data.
 *    - The tape is manipulated using a data pointer that can move left or right.
 *    - The function supports all Brainfuck commands, including loops.
 *    - The output is stored in a buffer and returned as a string.
 * 
 * 2. readAndExecuteFile(const char *filename):
 *    - This function reads Brainfuck code from a specified file.
 *    - It then calls the executeBrainfuck function to execute the code.
 *    - The output of the execution is printed to the standard output.
 * 
 * 3. main(int argc, char *argv[]):
 *    - The entry point of the program.
 *    - It expects one command-line argument: the name of the file containing Brainfuck code.
 *    - The function calls readAndExecuteFile to execute the Brainfuck code from the file.
 * 
 * Usage:
 * 
 * To compile the program:
 * gcc -o brainfuck_interpreter brainfuck_interpreter.c
 * 
 * To run the program:
 * ./brainfuck_interpreter <filename>
 * 
 * Example:
 * ./brainfuck_interpreter hello_world.bf
 * 
 * The file hello_world.bf should contain valid Brainfuck code.
 * 
 * Note:
 * - The program uses dynamic memory allocation and should be run on a system
 *   with sufficient memory.
 * - Error handling is included to manage file operations and memory allocation failures.
 * - The program uses the standard input for the ',' command in Brainfuck, which reads a single character.
 * 
 * Author: Vernon Stuurman
*/
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
                output_buffer[output_index++] = *ptr;
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
