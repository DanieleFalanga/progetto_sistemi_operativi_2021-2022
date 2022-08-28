CC=gcc
CFLAGS=-I.
DEPS = Threads/terminal_handler.h Threads/action_handler.h AuxiliarFunctions/aux_functions.h ProcessesInformation/proc_function.h SystemInformation/system_function.h Threads/take_system_info.h Threads/take_processes_info.h
OBJ = main.o Threads/terminal_handler.o Threads/action_handler.o AuxiliarFunctions/aux_functions.o ProcessesInformation/proc_function.o SystemInformation/system_function.o Threads/take_system_info.o Threads/take_processes_info.o


%.o: %.c $(DEPS)
	$(CC) -lm -pthread -g -c -o $@ $< $(CFLAGS) -lncurses 

similtop: $(OBJ)
	$(CC) -lm -pthread -g -o $@ $^ $(CFLAGS) -lncurses
