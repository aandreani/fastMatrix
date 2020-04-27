CC=gcc
CFLAGS=-mavx2 -msse2 -g
DEPS = fastMatrix.h matrix.h
OBJ = fastMatrix.o main.o matrix.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o test
