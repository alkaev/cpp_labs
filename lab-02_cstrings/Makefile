CC = gcc
CFLAGS=-Wall -Wextra -Werror -Iinclude

.PHONY: all clean

all: mkDirObj lab-02_cstrings

mkDirObj:
		mkdir -p obj


lab-02_cstrings:  obj/str.o obj/test.o obj/test_str.o 
		$(CC) $(CFLAGS) obj/str.o obj/test.o obj/test_str.o  -o lab-02_cstrings

obj/test_str.o include/test_str.h: src/test_str.c
		$(CC) $(CFLAGS) -c src/test_str.c -o obj/test_str.o

obj/test.o include/test.h: src/test.c
		$(CC) $(CFLAGS) -c src/test.c -o obj/test.o

obj/str.o include/str.h: src/str.c
		$(CC) $(CFLAGS) -c src/str.c -o obj/str.o


clean: 
	rm -rf obj lab-02_cstrings