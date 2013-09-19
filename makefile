CC=gcc
CFLAGS= -Wall -I. -pthread
DEPS = gaussian_print.h
OBJ = gaussian-add.o gauss_print.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

gaussian-add: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
