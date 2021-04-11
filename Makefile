OUTPUT = language
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic

$(OUTPUT): $(wildcard src/*.c)
	$(CC) $(CFLAGS) -o $(OUTPUT) src/include.c

install:
	make -B
	cp $(OUTPUT) /usr/local/bin/$(OUTPUT)