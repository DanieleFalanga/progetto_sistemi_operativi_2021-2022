CC=gcc
CFLAGS=-I.
DEPS = AuxiliarFunctions/aux_functions.h ProcessesInformation/proc_function.h SystemInformation/system_function.h Threads/take_info_system.h Threads/take_processes_info.h
OBJ = main.o AuxiliarFunctions/aux_functions.o ProcessesInformation/proc_function.o SystemInformation/system_function.o Threads/take_info_system.o Threads/take_processes_info.o


%.o: %.c $(DEPS)
	$(CC) -lm -lncurses -g -c -o $@ $< $(CFLAGS)

similtop: $(OBJ)
	$(CC) -lm -lncurses -g -o $@ $^ $(CFLAGS)
