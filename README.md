## Stack Machine

### Notations

In this documentation the top of the stack is denoted as 's0', the second topmost element as 's1', the third topmost element as 's2', and so on. The word placed at the next program-counter address is denoted 'np'.

### Instructions

1.  jump        (s0)      -> jump to the address stored in s0.
1.  jump_if     (s0, s1)  -> jump to the address stored in s0 if s1 is not 0.
1.  push        (np)      -> push n0 to the top of the stack.
1.  drop        (s0)      -> discard the top of the stack.
1.  dup         (s0)      -> duplicate s0 to the top of the stack.
1.  over        (s1)      -> duplicate s1 to the top of the stack.
1.  swap        (s0, s1)  -> swap s0 and s1.
1.  add         (s0, s1)  -> add s1 and s0 and push the result to the top of the stack.
1.  sub         (s0, s1)  -> subtract s1 and s0 and push the result to the top of the stack.
1.  mul         (s0, s1)  -> multiplie s1 and s0 and push the result to the top of the stack.
1.  div         (s0, s1)  -> divide s1 and s0 and push the result to the top of the stack.
1.  and         (s0, s1)  -> and s1 and s0 and push the result to the top of the stack.
1.  or          (s0, s1)  -> or s1 and s0 and push the result to the top of the stack.
1.  not         (s0)      -> negate s0 and push the result to the top of the stack.
1.  halt        ()        -> halt execution.
  * ? load      : add support to load data from memory to the top of stack the stack in the future.
  * ? store     : add support to store data from the top of stack the stack in to memory in the future.
  * ? call      : if we end up having a return stack.
  * ? return    : if we end up having a return stack.
