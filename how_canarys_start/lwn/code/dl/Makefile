CC=gcc
CFLAGS=-I.
OBJ:=main.out

all:$(OBJ)
$(OBJ):libmain.so
%.o:%.c
	$(CC) -c -o $@ $< $(CFLAGS) -g
libmain.so:libmain.o
	gcc -shared -o libmain.so libmain.o -fPIC
main.out:main.o
	gcc main.o -o main.out -L. -lmain -Wl,-rpath=`pwd`
