#include "take_processes_info.h"

#define QUIT "quit"
#define RESUME "resume"
#define KILL "kill"
#define SUSPEND "suspend"
#define EXIT "exit"
#define SHUTDOWN "shutdown"

extern int counter_row_min;

void* terminal_handler(void* arg);
