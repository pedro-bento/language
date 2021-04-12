void read_file_to_vm(const char file_path[], VM *vm) {
  FILE *fp = fopen(file_path, "r");
  panic(fp == NULL, stderr, "ERROR: Could not open file <%s>.\n", file_path);

  {
    u64 count, instructions_size; // memory_size;

    count = fread(&instructions_size, sizeof(instructions_size), 1, fp);
    panic(count != 1, stderr, "ERROR: Could not read number of instructions from file <%s>.\n", file_path);

    // count = fread(&memory_size, sizeof(memory_size), 1, fp);
    // panic(count != 1, stderr, "ERROR: Could not read memory size from file <%s>.\n", file_path);

    count = fread(vm->instructions, sizeof(vm->instructions[0]), instructions_size, fp);
    panic(count != instructions_size, stderr, "ERROR: Could not read instructions from file <%s>.\n", file_path);

    // count = fread(vm->memory, sizeof(vm->memory[0]), memory_size, fp);
    // panic(count != memory_size, stderr, "ERROR: Could not read memory from file <%s>.\n", file_path);
  }

  int err = fclose(fp);
  panic(err == EOF, stderr, "ERROR: Could not close file <%s>.\n", file_path);
}

void read_file_to_str(const char file_path[], char *str, u64 str_capacity) {
  FILE *fp = fopen(file_path, "r");
  panic(fp == NULL, stderr, "ERROR: Could not open file <%s>.\n", file_path);

  {
    i64 count, size;

    count = fseek(fp, 0, SEEK_END);
    panic(count != 0, stderr, "ERROR: Could not find end of file <%s>.\n", file_path);

    size = ftell(fp);
    panic(count == -1, stderr, "ERROR: Could not calculate file size <%s>.\n", file_path);
    panic((u64)size >= str_capacity, stderr, "ERROR: can not read in to str, not enough capacity <%s>.\n", file_path);

    count = fseek(fp, 0, SEEK_SET);
    panic(count != 0, stderr, "ERROR: Could not move to the begining of file <%s>.\n", file_path);

    count = fread(str, sizeof(str[0]), size, fp);
    panic(count != size, stderr, "ERROR: Could not write memory to file <%s>.\n", file_path);
  }

  int err = fclose(fp);
  panic(err == EOF, stderr, "ERROR: Could not close file <%s>.\n", file_path);
}