int main(int argc, char const *argv[]) {
  panic(argc < 2, stderr, "ERROR: %s.\n", "No input files given");

  Lexer lexer = {0};
  lexer.line = 1;
  strcpy(lexer.file_path, argv[1]);

  read_file_to_str(lexer.file_path, lexer.source, SOURCE_CAPACITY);

  Token token;
  while (lexer_next(&lexer, &token), token.type != TOKEN_END) {
    token_dump(&token);
  }

  return EXIT_SUCCESS;
}
