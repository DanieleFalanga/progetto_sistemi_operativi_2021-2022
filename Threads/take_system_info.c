#include "take_system_info.h"

void take_info_system(WINDOW* system_box){
    //Buffers
    float percentages[NUM_OF_CORES];
    float cpu_last_sum[NUM_OF_CORES];
    float cpu_last_idle[NUM_OF_CORES];
    char* stat_buffer[BUFFER_SIZE];
    char* mem_buffer[3];
    
    //Prendo i file che mi servono
    strtok_aux("/proc/stat", " ", stat_buffer);
    strtok_aux("/proc/meminfo", " ", mem_buffer);
    

    float p=take_mem_info(mem_buffer);

    take_cores_usage_percentages(percentages, cpu_last_sum, cpu_last_idle);
    
    int num_cpu = take_num_of_cores();


    
    //Stampo le info della Cpu come se fossero una matrice
    //Stampo per righe
    int count_cpu = 0;
    for(int i=1; i<8; i++){
        int j=0;
        while (count_cpu != num_cpu || j<3){
            mvwprintw(system_box, i, j*15+1, "CPU %d: %.1f% ",count_cpu, percentages[count_cpu]);    
            count_cpu++;
            j++;
        }
        j=0;
        if(count_cpu == num_cpu){
            break;
        }
    }
    
    
}