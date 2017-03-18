CC = gcc
LDFLAGS = -lpthread -rdynamic -ldl
CFLAGS = -Wall -Wextra
OBJECTS = main.o data.o io.o file.o

all: basic

basic: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)
	rm *.o

main.o: src/main.c src/io.h src/data.h src/file.h
	$(CC) $(CFLAGS) -c $<

data.o: src/data.c src/data.h
	$(CC) $(CFLAGS) -c $<

io.o: src/io.c src/io.h src/data.h
	$(CC) $(CFLAGS) -c $<

file.o: src/file.c src/file.h src/io.h src/data.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o
