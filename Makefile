CC=gcc
CFLAGS=-I.
DEPS = aux_function.h proc_function.h
OBJ = main.o aux_function.o proc_function.o

%.o: %.c $(DEPS)
	$(CC) -lm -c -o $@ $< $(CFLAGS)

similtop: $(OBJ)
	$(CC) -lm -o $@ $^ $(CFLAGS)
