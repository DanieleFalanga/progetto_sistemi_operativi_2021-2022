#include "take_processes_info.h"

//General function that takes all processes informations
void take_processes_info(char** group_buffer){
    //printf("%s\n", group_buffer[search_group_id("/proc/1152/status")]);

    for (int num_pid = 1; num_pid<100000; num_pid++){
        //initialize stat string
        char stat[100] = "/proc/";
        
        //take pid string
        char pid[5000];//(int)((ceil(log10(num_pid))+1)*sizeof(char))];
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
        
        //DA CONVERTIRE IN STRINGA
        int int_res = take_res(buffer_statm);
        char res[(int)((ceil(log10(int_res))+1)*sizeof(char))];//(int)((ceil(log10(num_pid))+1)*sizeof(char))];
        sprintf(res, "%d", int_res);

        int int_share = take_share(buffer_statm);
        char share[(int)((ceil(log10(int_share))+1)*sizeof(char))];//(int)((ceil(log10(num_pid))+1)*sizeof(char))];
        sprintf(share, "%d", int_share);

        char* status_string = take_status(buffer_stat);
        
        //DA CONVERTIRE IN STRINGA
        int int_time = take_time(buffer_stat);
        char time[(int)((ceil(log10(int_time))+1)*sizeof(char))];//(int)((ceil(log10(num_pid))+1)*sizeof(char))];
        sprintf(time, "%d", int_time);
        
        char cmdline_string[70];
        char* command_line = take_cmdline(cmdline, cmdline_string);
        
        //DA CONVERTIRE IN STRINGA
        double double_cpu_usage=take_cpu_usage_process(buffer_stat);
        char cpu_usage[50];//(int)((ceil(log10(num_pid))+1)*sizeof(char))];
        sprintf(cpu_usage, "%f", cpu_usage);


        mvprintw(10+num_pid, PID_COLUMN, pid);
        mvprintw(10+num_pid, USER_COLUMN, user);
        mvprintw(10+num_pid, PRI_COLUMN, priority);
        mvprintw(10+num_pid, NI_COLUMN, nice_value);
        mvprintw(10+num_pid, VIRT_COLUMN, virt);
        mvprintw(10+num_pid, RES_COLUMN, res);
        mvprintw(10+num_pid, SHR_COLUMN, share);
        mvprintw(10+num_pid, S_COLUMN, status_string);
        mvprintw(10+num_pid, CPU_COLUMN, time);
        mvprintw(10+num_pid, TIME_COLUMN, cmdline_string);
        mvprintw(10+num_pid, CMD_COLUMN, command_line);
        
        break;
        
    } 
}