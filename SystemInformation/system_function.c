#include "system_function.h"




//Daniele
float take_mem_info(char** buffer){
    float mem_percentage;
    char* mem_buffer[3] = {}; 
    //memtotal
    mem_buffer[0] = malloc(strlen(buffer[1])*sizeof(char*) +1);
    strcpy(mem_buffer[0], buffer[1]);
    //memFree
    mem_buffer[1] = malloc(strlen(buffer[4])*sizeof(char*) +1);
    strcpy(mem_buffer[1], buffer[4]);
    //memAvailable
    mem_buffer[2] = malloc(strlen(buffer[7])*sizeof(char*) +1);
    strcpy(mem_buffer[2], buffer[7]);

    float mem_total = atoi(mem_buffer[0]);
    float mem_available = atoi(mem_buffer[1]) + atoi(mem_buffer[2]);
    float mem_used = mem_total - mem_available;
    mem_percentage = (mem_used/mem_total) * 100;
    //printf("eccomi\n");
    return mem_percentage;
}

//Daniele
/*Uptime in seconds*/
double take_uptime(char* path_memfile){
    double uptime;
    char* uptime_buffer[2] = {};
    strtok_aux(path_memfile, " ", uptime_buffer);
    uptime = atof(uptime_buffer[0]);
    return uptime;
}


//Flavio
int take_num_of_cores(){
    return search_first_occurrence("/proc/stat", "\n", "intr ") - 1;
}

//Flavio
char* take_num_running_processes(){
    char* path="/proc/stat";
    char* str_buffer[BUFFER_SIZE];
    char* delimiter=" ";
    strtok_aux(path, delimiter, str_buffer);

    return str_buffer[1292];
}
//Flavio
char* take_num_blocked_processes(){
    char* path="/proc/stat";
    char* str_buffer[BUFFER_SIZE];
    char* delimiter=" ";
    strtok_aux(path, delimiter, str_buffer);

    return str_buffer[1294];
}

//Flavio
void take_first_cores_usage_percentages(float* percentages, float* cpu_last_sum, float* cpu_last_idle){
    char* line_buffer[BUFFER_SIZE];
    strtok_aux("/proc/stat", "\n", line_buffer);
    
    //for every core
    for(int i=1; i< NUM_OF_CORES+1 ; i++){
        int counter_idle=1;
        float cpu_current_sum=0;
        float cpu_current_idle=0;

        //calculate of the cpu_sum and of cpu_idle
        char* token=strtok(line_buffer[i], " ");
//        printf("token inutile.............%s\n", token);
        token = strtok(NULL, " ");
        while(token!=NULL){
            printf("%s\n", token);
            if(counter_idle==4)
                cpu_current_idle=atof(token);
            cpu_current_sum += (atof(token));
            counter_idle+=1;
            token = strtok(NULL, " ");

        }
        cpu_last_sum[i-1]=cpu_current_sum;
        cpu_last_idle[i-1]=cpu_current_idle;
    }
}

//Flavio
/*Calculate percentages of usage of every single core.
  Insert percentages in a buffer */
void take_cores_usage_percentages(float* percentages, float* cpu_last_sum, float* cpu_last_idle){
    char* line_buffer[BUFFER_SIZE];
    strtok_aux("/proc/stat", "\n", line_buffer);

    //for every core
    for(int i=1; i< NUM_OF_CORES+1 ; i++){
        int counter_idle=1;
        float cpu_current_sum=0;
        float cpu_current_idle=0;

        //calculate of the cpu_sum and cpu_idle
        char* token=strtok(line_buffer[i], " ");
        token = strtok(NULL, " ");
        while(token!=NULL){
            if(counter_idle==4)
                cpu_current_idle=atof(token);
            cpu_current_sum += (atof(token));
            counter_idle+=1;
            token = strtok(NULL, " ");

        }
        //printf("sum: %f\n", cpu_current_sum);
        //printf("idle: %f\n", cpu_current_idle);
        //calculate of the percentage
        float cpu_sum_delta = cpu_current_sum - cpu_last_sum[i-1];   //       printf("sum delta: %f\n", cpu_sum_delta);

        float cpu_idle_delta = cpu_current_idle - cpu_last_idle[i-1];  //         printf("idle delta: %f\n", cpu_idle_delta);


        float cpu_used = cpu_sum_delta - cpu_idle_delta;   //     printf("used: %f\n", cpu_used);

        float cpu_usage_percentage = (float) (cpu_used/cpu_sum_delta); //       printf("usage: %f\n\n\n", cpu_usage_percentage);

        percentages[i-1]=(cpu_usage_percentage*100);
        //printf("percentage core %d:\t%.2f\n\n\n", i-1, percentages[i-1]);

        //update of the last values with the current values
        cpu_last_sum[i-1]=cpu_current_sum;
        cpu_last_idle[i-1]=cpu_current_idle;
    }      
}

