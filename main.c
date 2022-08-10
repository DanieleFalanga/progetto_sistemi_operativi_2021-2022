#include "aux_function.h"


int main(int argc, char** argv){

    char* str_buffer[BUFFER_SIZE] = {};
    strtok_aux("/proc/stat", " ", str_buffer);
        
    float ram_percentage = take_mem_info("/proc/meminfo");
    printf("USED RAM: %.2f%\n", ram_percentage);
    printf("UPTIME: %.2f \n", UPTIME);
    printf("%s\n", take_num_running_processes());
    printf("%s\n", take_num_blocked_processes());
    printf("%d", NUM_OF_CORES);

    float percentages[NUM_OF_CORES];                    //da fixare
    take_cores_usage_percentages(percentages);          //
    for(int i=0; i<NUM_OF_CORES; i++)                   //
        printf("%f\n", percentages[i]);                 //
    printf("\n");                                       //

    int buffer_indices[1000];
    searc_all_occurrences("/proc/stat", "\n", "cpu", buffer_indices);
    for(int i=0; i<16; i++)
        printf("%d\n", buffer_indices[i]);
    

    return 0;
}

