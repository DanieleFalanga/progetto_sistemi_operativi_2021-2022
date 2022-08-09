#include "aux_function.h"


int main(int argc, char** argv){
    char* str_buffer[BUFFER_SIZE] = {};
    strtok_aux("/proc/stat", " ", str_buffer);
    //printf("%s\n", str_buffer[3]);

    printf("%d", NUM_OF_CORES);
    return 0;
}

