#include "take_system_info.h"

void print_system_info(WINDOW* system_box, float* percentages, float mem_info, char* num_blocked_processes, char* num_running_processes){
    for(int i=0; i<NUM_OF_CORES; i++){
        if(i%4==0)
            mvwprintw(system_box, i/4 +1, 5, "CPU %d: %.2f", i, percentages[i]);
        else if(i%4==1)
            mvwprintw(system_box, i/4 +1, 20, "CPU %d: %.2f", i, percentages[i]);
        else if(i%4==2)
            mvwprintw(system_box, i/4 +1, 35, "CPU %d: %.2f", i, percentages[i]);
        else if(i%4==3)
            mvwprintw(system_box, i/4 +1, 50, "CPU %d: %.2f", i, percentages[i]);
    }
    mvwprintw(system_box, 7, 5, "number of blocked processes: %s", num_blocked_processes);
    mvwprintw(system_box, 8, 5, "number of running processes: %s", num_running_processes);
    mvwprintw(system_box, 6, 5, "percentage of memory use: %.2f", mem_info);
}



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
    
    char* num_blocked_processes=take_num_blocked_processes(stat_buffer);
    char* num_running_processes=take_num_running_processes(stat_buffer);
    //printf("%s\n", num_blocked_processes);
    //printf("%s\n", num_running_processes);




    float mem_info=take_mem_info(mem_buffer);
    /*char mem_info[6];
    sprintf(mem_info, "%.2f", fabs(p));
    //printf("%s\n", mem_info);
*/
    take_cores_usage_percentages(percentages, cpu_last_sum, cpu_last_idle);
    print_system_info(system_box, percentages, mem_info, num_blocked_processes, num_running_processes);


    
    //Stampo le info della Cpu come se fossero una matrice
    //Stampo per righe
   /* int count_cpu = 0;
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
    }*/
    
    
}