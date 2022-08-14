#include "take_processes_info.h"

//General function that takes all processes informations
void take_processes_info(char** group_buffer){
    //printf("%s\n", group_buffer[search_group_id("/proc/1152/status")]);

    for (int num_pid = 1; num_pid<100000; num_pid++){
        //initialize stat string
        char stat[100] = "/proc/";
        
        //take pid string
        char pid[(int)((ceil(log10(num_pid))+1)*sizeof(char))];
        sprintf(pid, "%d", num_pid);
        
        //first strcat, util for sanity check above
        strcat(stat, pid);
        strcat(stat, "/stat");
        
        //Sanity check
        if(fopen(stat, "r") == NULL)
            continue; 
        
        char* buffer_stat[BUFFER_SIZE];
        strtok_aux(stat, " ", buffer_stat);
        
        if (strcmp(buffer_stat[0], buffer_stat[5]) != 0)
            continue;

        //initialize others paths and do other strcat  
        char statm[100] = "/proc/";
        char cmdline[100] = "/proc/";
        char status[100] = "/proc/";
        strcat(statm, pid);
        strcat(statm, "/statm");
        strcat(cmdline, pid);
        strcat(cmdline, "/cmdline");
        strcat(status, pid);
        strcat(status, "/status");
        

        //take buffers with strtok_aux
        //Not necessary for cmdline and status
        
        char* buffer_statm[BUFFER_SIZE];
        
        strtok_aux(statm, " ", buffer_statm);
        
        //take all necessary parameters with the appropriate functions
        char* user = group_buffer[search_group_id(status)];
        char* priority = take_priority(buffer_stat);
        char* nice_value = take_nice_value(buffer_stat);
        char* virt = take_virt(buffer_stat);
        int res = take_res(buffer_statm);
        int share = take_share(buffer_statm);
        char* status_string = take_status(buffer_stat);
        int time = take_time(buffer_stat);
        char cmdline_string[70];
        char* command_line = take_cmdline(cmdline, cmdline_string);
        double cpu_usage=take_cpu_usage_process(buffer_stat);
                
        
        printf("%s\n", pid);
        
        printf("user: %s\n", user);
        printf("PRI: %s\n", priority);
        printf("NI: %s\n", nice_value); //errato
        printf("VIRT: %s\n", virt);
        printf("RES: %d\n", res); //errato

        printf("SHARE: %d\n", share); //errato
        printf("STATUS: %s\n", status_string);
        printf("CPU:  %lf%\n", cpu_usage);
        printf("TIME: %d\n", time); //errato
        printf("CMD: %s\n", command_line);
        break;
        
    } 
}