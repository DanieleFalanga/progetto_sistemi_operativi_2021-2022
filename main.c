#include "proc_function.h"


int main(int argc, char** argv){
    //informazioni statiche e buffer
    char* group_buffer[65534];
    take_group_info(group_buffer);
    
    
    /*
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
       
 //   float ram_percentage = take_mem_info("/proc/meminfo");

 //   printf("USED RAM: %.2f%\n", ram_percentage);
    printf("UPTIME: %.2f \n", UPTIME);
    printf("%s\n", take_num_running_processes());
    printf("%s\n", take_num_blocked_processes());
    printf("%d\n\n\n\n", NUM_OF_CORES);




/////////////////////////////////////////////////       da fixare

    float percentages[NUM_OF_CORES];
    float cpu_last_sum[NUM_OF_CORES];
    float cpu_last_idle[NUM_OF_CORES];
    char* line_buffer[BUFFER_SIZE];
    strtok_aux("/proc/stat", "\n", line_buffer);
    
    //for every core
    for(int i=1; i< NUM_OF_CORES+1 ; i++){
        int counter_idle=0;
        float cpu_current_sum=0;
        float cpu_current_idle;

        //calculate of the cpu_sum and of the idle
        char* token=strtok(line_buffer[i], " ");
        
        token = strtok(NULL, " ");
        while(token!=NULL){
            if(counter_idle==4)
                cpu_current_idle=atof(token);
            cpu_current_sum+= (atof(token));
            counter_idle+=1;
            token = strtok(NULL, " ");

        }
        cpu_last_sum[i]=cpu_current_sum;
        cpu_last_idle[i]=cpu_current_idle;
    }
    sleep(1);
    take_cores_usage_percentages(percentages, cpu_last_sum, cpu_last_idle);

    for(int i=0; i<NUM_OF_CORES; i++){
        printf("%f\n", percentages[i]);
    }

    */
    take_processes_info();
    
    return 0;
}

