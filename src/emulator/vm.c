#define INSTRUCTIONS_CAPACITY KB(32)
#define STACK_CAPACITY KB(64)

typedef struct {
  Instruction instructions[INSTRUCTIONS_CAPACITY];
  Word stack[STACK_CAPACITY];
  u64 ip;
  u64 sp;
} VM;

void vm_execute_instruction(VM *vm) {
  vm->ip += 1;
}

void vm_execute(VM *vm) {
  while (vm->instructions[vm->ip]) {
    vm_execute_instruction(vm);
  }
}