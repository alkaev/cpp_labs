CC = g++
CFLAGS=-Wall -Wextra -Werror -Iinclude

.PHONY: all clean

all: mkDirObj lab-07_matrix

mkDirObj:
		mkdir -p obj


lab-07_matrix:  obj/main.o obj/matrix.o 
		$(CC) $(CFLAGS)  obj/main.o obj/matrix.o  -o lab-07_matrix

obj/matrix.o include/matrix.h: src/matrix.cpp
		$(CC) $(CFLAGS) -c src/matrix.cpp -o obj/matrix.o

obj/main.o: src/main.cpp
		$(CC) $(CFLAGS) -c src/main.cpp -o obj/main.o


clean: 
	rm -rf obj lab-07_matrix