void file_read_program(const char file_path[], VM *vm) {
  FILE *fp = fopen(file_path, "r");
  panic(fp == NULL, stderr, "ERROR: Could not open file <%s>.\n", file_path);

  size_t count;

  count = fread(&vm->instructions_size, sizeof(vm->instructions_size), 1, fp);
  panic(count != 1, stderr,
        "ERROR: Could not read number of instructions from file <%s>.\n",
        file_path);

  count = fread(&vm->memory_size, sizeof(vm->memory_size), 1, fp);
  panic(count != 1, stderr,
        "ERROR: Could not read memory size from file <%s>.\n", file_path);

  count = fread(vm->instructions, sizeof(vm->instructions[0]),
                vm->instructions_size, fp);
  panic(count != vm->instructions_size, stderr,
        "ERROR: Could not read instructions from file <%s>.\n", file_path);

  count = fread(vm->memory, sizeof(vm->memory[0]), vm->memory_size, fp);
  panic(count != vm->memory_size, stderr,
        "ERROR: Could not read memory from file <%s>.\n", file_path);

  int err = fclose(fp);
  panic(err == EOF, stderr, "ERROR: Could not close file <%s>.\n", file_path);
}

void file_write_program(const char file_path[], const Program *program) {
  FILE *fp = fopen(file_path, "w");
  panic(fp == NULL, stderr, "ERROR: Could not open file <%s>.\n", file_path);

  size_t count;

  count = fwrite(&program->instructions_size,
                 sizeof(program->instructions_size), 1, fp);
  panic(count != 1, stderr,
        "ERROR: Could not write number of instructions to file <%s>.\n",
        file_path);

  count = fwrite(&program->memory_size, sizeof(program->memory_size), 1, fp);
  panic(count != 1, stderr,
        "ERROR: Could not write memory size to file <%s>.\n", file_path);

  count = fwrite(program->instructions, sizeof(program->instructions[0]),
                 program->instructions_size, fp);
  panic(count != program->instructions_size, stderr,
        "ERROR: Could not write instructions to file <%s>.\n", file_path);

  count = fwrite(program->memory, sizeof(program->memory[0]),
                 program->memory_size, fp);
  panic(count != program->memory_size, stderr,
        "ERROR: Could not write memory to file <%s>.\n", file_path);

  int err = fclose(fp);
  panic(err == EOF, stderr, "ERROR: Could not close file <%s>.\n", file_path);
}