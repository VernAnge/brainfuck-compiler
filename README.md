# Brainfuck Compiler in C

This project contains a simple Brainfuck compiler written in C. The compiler reads Brainfuck code from a file and executes it.

## Directory Structure

project/
│
├── src/
│ └── brainfuck.c
│
├── test/
│ ├── test1.bf
│ ├── test1.out
│ ├── test2.bf
│ ├── test2.out
│ ├── test3.bf
│ ├── test3.out
│ ├── test4.bf
│ ├── test4.out
│ ├── test5.bf
│ ├── test5.out
│ ├── test6.bf
│ ├── test6.out
│ ├── test7.bf
│ ├── test7.out
│ ├── test8.bf
│ ├── test8.out
│ ├── test9.bf
│ ├── test9.out
│ ├── test10.bf
│ ├── test10.out
│ └── run_tests.sh
│
├── .gitignore

├──run_tests.sh
└── README.md

## Test Scripts

## Compilation and Execution

1. **Compile the Brainfuck compiler:**

   ```sh
   gcc src/brainfuck.c -o brainfuck
   ```
2. **Run the compiler with a Brainfuck script:**

   ```sh
   ./brainfuck test/test1.bf
   ```

## Running Tests

To run the tests, execute the following script:

```sh
chmod +x run_tests.sh
./run_tests.sh
```

The `test` directory contains 10 simple Brainfuck scripts for testing.

## Brainfuck Language

Brainfuck is a minimalist programming language consisting of only eight commands:

- `>`: Increment the data pointer.
- `<`: Decrement the data pointer.
- `+`: Increment the byte at the data pointer.
- `-`: Decrement the byte at the data pointer.
- `.`: Output the byte at the data pointer.
- `,`: Input a byte and store it at the data pointer.
- `[`: Jump past the matching `]` if the byte at the data pointer is zero.
- `]`: Jump back to the matching `[` if the byte at the data pointer is nonzero.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.
