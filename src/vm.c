typedef enum {
  WRITE_I64 = 0,
  WRITE_CHAR,

  READ_SYSCALLS,

  READ_I64,
  READ_CHAR,
} Syscall_Type;

typedef enum {
  HALT = 0,
  PUSH,
  POP,
  ADD,
  SYSCALL,
} Instruction_Type;

typedef struct {
  Instruction instructions[INSTRUCTIONS_CAPACITY];
  u64 instructions_size;

  Word memory[MEMORY_CAPACITY];
  u64 memory_size;

  Word stack[STACK_CAPACITY];

  u64 ip;
  u64 sp;

} VM;

void vm_execute_instruction(VM *vm) {
  switch (vm->instructions[vm->ip]) {
  case PUSH:
    panic(vm->sp > STACK_CAPACITY, stderr, "ERROR: stack overflow.\n");
    vm->stack[vm->sp].as_u8 = vm->instructions[vm->ip + 1];
    vm->sp += 1;
    vm->ip += 2;
    break;

  case POP:
    panic(vm->sp < 1, stderr, "ERROR: stack underflow <sp: %d>.\n", vm->sp);
    vm->sp -= 1;
    vm->ip += 1;
    break;

  case ADD:
    panic(vm->sp < 2, stderr, "ERROR: stack underflow <sp: %d>.\n", vm->sp);
    vm->stack[vm->sp - 2].as_i64 =
        vm->stack[vm->sp - 2].as_i64 + vm->stack[vm->sp - 1].as_i64;
    vm->sp -= 1;
    vm->ip += 1;
    break;

  case SYSCALL:
    panic(vm->sp < 1, stderr, "ERROR: stack underflow <sp: %d>.\n", vm->sp);

    u8 type = vm->stack[vm->sp - 1].as_u8;
    panic(type < READ_SYSCALLS && vm->sp < 2, stderr, "ERROR: stack underflow <sp: %d>.\n", vm->sp);

    switch (type) {
    case WRITE_I64:
      fprintf(stdout, "%ld", vm->stack[vm->sp - 2].as_i64);
      vm->sp -= 2;
      vm->ip += 1;
      break;

    case WRITE_CHAR:
      fprintf(stdout, "%c", (char)vm->stack[vm->sp - 2].as_u8);
      vm->sp -= 2;
      vm->ip += 1;
      break;

    case READ_I64:
      fscanf(stdin, "%ld", &vm->stack[vm->sp - 1].as_i64);
      vm->ip += 1;
      break;

    case READ_CHAR:
      fscanf(stdin, "%c", &vm->stack[vm->sp - 1].as_u8);
      vm->ip += 1;
      break;

    default:
      panic(true, stderr, "ERROR: Unknown syscall <%u>.\n", type);
      break;
    }

    break;

  case HALT:
    break;
  }
}

void vm_execute(VM *vm) {
  while (vm->instructions[vm->ip]) {
    vm_execute_instruction(vm);
  }
}