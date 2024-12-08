CC = g++
CFLAGS=-Wall -Wextra -Werror -Iinclude

.PHONY: all clean

all: mkDirObj lab-06_int-vector

mkDirObj:
		mkdir -p obj


lab-06_int-vector:  obj/main.o obj/my_vector.o 
		$(CC) $(CFLAGS)  obj/main.o obj/my_vector.o  -o lab-06_int-vector

obj/my_vector.o include/my_vector.hpp: src/my_vector.cpp
		$(CC) $(CFLAGS) -c src/my_vector.cpp -o obj/my_vector.o

obj/main.o: src/main.cpp
		$(CC) $(CFLAGS) -c src/main.cpp -o obj/main.o


clean: 
	rm -rf obj lab-06_int-vector