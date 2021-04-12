#define KB(N) (1024 * N)
#define MB(N) (KB(1024) * N)

typedef int64_t i64;
typedef uint64_t u64;

typedef union {
  i64 as_i64;
} Word;

typedef u64 Instruction; // 8 bytes
typedef enum {
  HALT = 0,
  JUMP,
  JUMP_IF,
  PUSH,
  DROP,
  DUP,
  OVER,
  ADD,
  SUB,
  MUL,
  DIV,
  AND,
  OR,
  NOT
} Instruction_Type;
