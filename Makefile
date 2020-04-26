CC=gcc
CFLAGS=-mavx2 -msse2 -O2
DEPS = fastMatrix.h
OBJ = fastMatrix.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)