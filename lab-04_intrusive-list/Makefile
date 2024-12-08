CC = gcc
CFLAGS=-Wall -Wextra -Werror -Iinclude

.PHONY: all clean



all: mkDirObj lab-04_intrusive-list

mkDirObj:
		mkdir -p obj



lab-04_intrusive-list: obj/clist.o obj/main.o
		$(CC) $(CFLAGS) obj/clist.o obj/main.o -o lab-04_intrusive-list

obj/clist.o obj/clist.h: src/clist.c
		$(CC) $(CFLAGS) -c src/clist.c -o obj/clist.o

obj/main.o: src/main.c
		$(CC) $(CFLAGS) -c src/main.c -o obj/main.o


clean:
	rm -rf obj lab-04_intrusive-list
