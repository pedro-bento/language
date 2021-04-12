#define SOURCE_CAPACITY MB(4)
#define FILE_PATH_CAPACITY 256

#define SYMBOL_CAPACITY 128
#define INTEGER_CAPACITY 18

typedef enum {
  TOKEN_SYMBOL,
  TOKEN_INTEGER,
  TOKEN_END,
} Token_Type;

typedef union {
  i64 integer;
  char symbol[SYMBOL_CAPACITY];
} Token_Value;

typedef struct {
  Token_Type type;
  Token_Value value;
} Token;

typedef struct {
  char source[SOURCE_CAPACITY];
  char file_path[FILE_PATH_CAPACITY];
  u64 index;
  u64 line;
  u64 column;
} Lexer;

#define lexer_current_char(LEXER) (LEXER)->source[(LEXER)->index]

void lexer_advance_char(Lexer *lexer) {
  if (lexer_current_char(lexer) == '\n') {
    lexer->line += 1;
    lexer->column = 1;
  }
  lexer->index += 1;
}

void lexer_advance_whitespaces(Lexer *lexer) {
  while (isspace(lexer_current_char(lexer))) {
    lexer_advance_char(lexer);
  }
}

void lexer_advance_comment(Lexer *lexer) {
  if (lexer_current_char(lexer) == ';') {
    lexer_advance_char(lexer);
    if (lexer_current_char(lexer) == ';') {
      lexer_advance_char(lexer);
      while (lexer_current_char(lexer) != '\n' && lexer_current_char(lexer) != '\0') {
        lexer_advance_char(lexer);
      }
      if (lexer_current_char(lexer) != '\0') {
        lexer_advance_char(lexer);
      }
    } else {
      panic(true, stderr, "%s:%ld:%ld: ERROR: expected comment, found just one `;`.\n", lexer->file_path, lexer->line, lexer->column);
    }
  }
}

void lexer_next(Lexer *lexer, Token *token) {
  // White Spaces.
  lexer_advance_whitespaces(lexer);

  // Coments.
  while (lexer_current_char(lexer) == ';') {
    lexer_advance_comment(lexer);
  }

  // End of source.
  if (lexer->source[lexer->index] == '\0') {
    token->type = TOKEN_END;
    return;
  }

  // Tokens.
  if (isalpha(lexer_current_char(lexer))) {
    token->type = TOKEN_SYMBOL;
    u64 symbol_size = 0;

    while (isalnum(lexer_current_char(lexer)) || lexer_current_char(lexer) == '_' || lexer_current_char(lexer) == ':') {
      if (symbol_size >= SYMBOL_CAPACITY - 1) {
        panic(true, stderr, "%s:%ld:%ld: ERROR: reached maximum symbol size, %d characters.\n", lexer->file_path, lexer->line, lexer->column,
              SYMBOL_CAPACITY);
      }
      token->value.symbol[symbol_size++] = lexer_current_char(lexer);
      lexer_advance_char(lexer);
    }

    token->value.symbol[symbol_size] = '\0';
    return;
  } else if (isdigit(lexer_current_char(lexer))) {
    token->type = TOKEN_INTEGER;
    char integer_str[INTEGER_CAPACITY + 1];
    u64 integer_size = 0;

    while (isdigit(lexer_current_char(lexer))) {
      if (integer_size >= INTEGER_CAPACITY) {
        panic(true, stderr, "%s:%ld:%ld: ERROR: reached maximum integer size, %d digits.\n", lexer->file_path, lexer->line, lexer->column,
              INTEGER_CAPACITY);
      }
      integer_str[integer_size++] = lexer_current_char(lexer);
      lexer_advance_char(lexer);
    }

    integer_str[integer_size] = '\0';
    token->value.integer = strtoll(integer_str, NULL, 10);
    // TODO: check over and underflows;
    return;
  } else {
    panic(true, stderr, "%s:%ld:%ld: ERROR: could not begin token with character `%c` = %d.\n", lexer->file_path, lexer->line, lexer->column,
          lexer_current_char(lexer), (int)lexer_current_char(lexer));
  }
}

void token_dump(Token *token) {
  switch (token->type) {
  case TOKEN_SYMBOL:
    printf("[SYMBOL: %s]\n", token->value.symbol);
    break;
  case TOKEN_INTEGER:
    printf("[INTEGER: %ld]\n", token->value.integer);
    break;
  case TOKEN_END:
    printf("[END]\n");
    break;
  }
}