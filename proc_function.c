#include "proc_function.h"



void take_processes_info(){
    char** group_buffer[BUFFER_SIZE];
    strtok_aux("/etc/group"," \n",group_buffer);
}