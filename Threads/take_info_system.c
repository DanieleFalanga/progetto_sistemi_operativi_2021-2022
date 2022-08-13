#include "take_info_system.h"

void take_info_system(){
    float percentages[NUM_OF_CORES];
    float cpu_last_sum[NUM_OF_CORES];
    float cpu_last_idle[NUM_OF_CORES];
    char* stat_buffer[BUFFER_SIZE];
    strtok_aux("/proc/stat", " ", stat_buffer);
    char* mem_buffer[3];
    strtok_aux("/proc/meminfo", " ", mem_buffer);
    float p=take_mem_info(mem_buffer);
    printf("%.2f\n", p);

    take_cores_usage_percentages(percentages, cpu_last_sum, cpu_last_idle);

}