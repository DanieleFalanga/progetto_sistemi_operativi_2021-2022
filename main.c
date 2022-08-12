#include "proc_function.h"


int main(int argc, char** argv){
    //informazioni statiche e buffer
    char* group_buffer[65534];
    take_group_info(group_buffer);    

    /*
    char* str_buffer[BUFFER_SIZE] = {};
    strtok_aux("/proc/stat", " ", str_buffer);
    
    //Servono nel main
    float percentages[NUM_OF_CORES];
    float cpu_last_sum[NUM_OF_CORES];
    float cpu_last_idle[NUM_OF_CORES];
    //

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
       
 //   float ram_percentage = take_mem_info("/proc/meminfo");

 //   printf("USED RAM: %.2f%\n", ram_percentage);
    printf("UPTIME: %.2f \n", UPTIME);
    printf("%s\n", take_num_running_processes());
    printf("%s\n", take_num_blocked_processes());
    printf("%d\n\n\n\n", NUM_OF_CORES);


*/

    
/*    take_info_system();
    printf("info system:\n");
*/    take_processes_info(group_buffer);



    return 0;

}

