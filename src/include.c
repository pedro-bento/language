// We are using a single compilation unit, for more information visit,
// https://en.wikipedia.org/wiki/Single_Compilation_Unit
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

// Sources.
// Make sure you include them by order of dependency,
// for example, if A depends on B include A first then B.
#include "error.c"
#include "data.c"
#include "compiler/lexer.c"
#include "emulator/vm.c"
#include "io.c"
#include "main.c"