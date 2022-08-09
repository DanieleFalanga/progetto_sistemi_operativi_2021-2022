CC=gcc
CFLAGS=-I.
DEPS = aux_function.h
OBJ = main.o aux_function.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

similtop: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)