#define KB(N) (1024 * N)
#define MB(N) (KB(1024) * N)

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define INSTRUCTIONS_CAPACITY KB(4)
#define STACK_CAPACITY KB(12)
#define MEMORY_CAPACITY KB(48)

typedef u8 Instruction;
typedef union {
  u8 as_u8;
  i64 as_i64;
} Word;

typedef struct {
  Instruction instructions[INSTRUCTIONS_CAPACITY];
  u64 instructions_size;
  Word memory[MEMORY_CAPACITY];
  u64 memory_size;
} Program;