CC = gcc
CFLAGS = -Wall -Wextra

all = my_program

my_program: main.o avl_tree.o
	  $(CC) $(CFLAGS) -o my_program main.o avl_tree.o

main.o: main.c avl_tree.h
	  $(CC) $(CFLAGS) -c -o main.o main.c

avl_tree.o: avl_tree.c avl_tree.h
	  $(CC) $(CFLAGS) -c -o avl_tree.o avl_tree.c

clean:
	  rm -f my_program main.o avl_tree.o