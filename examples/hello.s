;; Define new instructions
define push3_zeros as
  push 3
  loop:
    push 0
    swap
    push 1
    sub
    push loop
  jump_if
end

;; Call instructions.
push3_zeros
push 21
push 21
add

;; Stack should contain:
;; 42 0 0 0