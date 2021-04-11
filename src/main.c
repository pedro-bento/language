#define WORD_ARRAY_CAPACITY KB(256)

int main(int argc, char const *argv[]) {
  {

    Program read_2_numbers_and_write_result = {
        .instructions =
            {
                // Write '> ' to stdout.
                PUSH,
                '>',
                PUSH,
                WRITE_CHAR,
                SYSCALL,
                PUSH,
                ' ',
                PUSH,
                WRITE_CHAR,
                SYSCALL,
                // Read i64 from stdin.
                PUSH,
                READ_I64,
                SYSCALL,
                // Write '> ' to stdout.
                PUSH,
                '>',
                PUSH,
                WRITE_CHAR,
                SYSCALL,
                PUSH,
                ' ',
                PUSH,
                WRITE_CHAR,
                SYSCALL,
                // Read i64 from stdin.
                PUSH,
                READ_I64,
                SYSCALL,
                // Add inputed values.
                ADD,
                // Write i64 and a newline to stdout.
                PUSH,
                WRITE_I64,
                SYSCALL,
                PUSH,
                '\n',
                PUSH,
                WRITE_CHAR,
                SYSCALL,
                // Halt the program.
                HALT,
            },
    };

    read_2_numbers_and_write_result.instructions_size =
        sizeof(read_2_numbers_and_write_result.instructions) /
        read_2_numbers_and_write_result.instructions[0];

    read_2_numbers_and_write_result.memory_size = 0;

    file_write_program("./examples/byte_code", &read_2_numbers_and_write_result);
  }

  {
    panic(argc < 2, stderr, "ERROR: %s.\n", "No input files given");

    VM vm = {0};
    file_read_program(argv[1], &vm);

    vm_execute(&vm);
  }

  return EXIT_SUCCESS;
}
