#
#
# makefile for hfd
#
# updated 29nov12



CC=gcc
CFLAGS= -Wall -I.
DEPS = hfd_print.h
OBJ = guassian-add.o guass_print.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

guassian-add: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
