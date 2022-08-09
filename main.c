#include "aux_function.h"


int main(int argc, char** argv){
    char* str_buffer[BUFFER_SIZE] = {};
    strtok_aux("/proc/stat", " ", str_buffer);
        
    float ram_percentage = take_mem_info("/proc/meminfo");
    printf("USED RAM: %.2f%\n", ram_percentage);
    printf("UPTIME: %.2f \n", UPTIME);
    printf("%d\n", NUM_OF_CORES);
    return 0;
}

