CC=gcc
CFLAGS=-Wall -I. -pthread
LDFLAGS=-pthread
SOURCES=gaussian-add.c gauss_print.h gauss_print.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=gaussian-add

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)