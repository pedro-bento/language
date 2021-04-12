void panic(bool condition, FILE *stream, const char *format, ...) {
  if (condition) {
    va_list args;
    va_start(args, format);
    vfprintf(stream, format, args);
    va_end(args);
    exit(EXIT_FAILURE);
  }
}