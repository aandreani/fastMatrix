CC=gcc
CFLAGS=-mavx2 -sse2 -O2
DEPS = fastMatrix.h
OBJ = fastMatrix.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)