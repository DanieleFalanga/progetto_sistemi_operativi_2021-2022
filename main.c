#include "aux_function.h"


int main(int argc, char** argv){
    char* str_buffer[BUFFER_SIZE] = {};
    char* mem[3] = {};
    float ram_percentage = mem_info("/proc/meminfo", mem);
    printf("USED RAM: %2.f%\n", ram_percentage);
    
    return 0;
}

