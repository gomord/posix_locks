CC=gcc
CFLAGS=-I.
OBJ:=show_info.out do_execve.out
all:$(OBJ)
%.out:%.c
	$(CC) -o $@ $< $(CFLAGS) -g
