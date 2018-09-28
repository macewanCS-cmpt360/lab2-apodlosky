CC = gcc
CFLAGS = -Wall -g

default: all

all: shell q1 q2 q3 q7

q1:
	$(CC) $(CFLAGS) q1.c -o q1

q2:
	$(CC) $(CFLAGS) q2.c -o q2

q3:
	$(CC) $(CFLAGS) q3.c -o q3

q7:
	$(CC) $(CFLAGS) q7.c -o q7

shell:
	$(CC) $(CFLAGS) shell.c -o shell

style:
	-/tmp/cmpt360/checkpatch.pl --no-tree --file --terse *.c

clean:
	-rm -f q1 q2 q2.txt q3 q7 shell
