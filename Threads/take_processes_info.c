#include "take_processes_info.h"

//General function that takes all processes informations
void take_processes_info(char** group_buffer, WINDOW* process_label){
    //printf("%s\n", group_buffer[search_group_id("/proc/1152/status")]);
    int row = 1;
    for (int num_pid = 1; num_pid<10000; num_pid++){
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
        int res = take_res(buffer_statm);
        //char res[(int)((ceil(log10(int_res))+1)*sizeof(char))];//(int)((ceil(log10(num_pid))+1)*sizeof(char))];
        //sprintf(res, "%d", int_res);
        
        int share = take_share(buffer_statm);
        //char share[(int)((ceil(log10(int_share))+1)*sizeof(char))];//(int)((ceil(log10(num_pid))+1)*sizeof(char))];
        //sprintf(share, "%d", int_share);
        
        char* status_string = take_status(buffer_stat);
        
        //DA CONVERTIRE IN STRINGA
        int time = take_time(buffer_stat);
        //char time[500];//(int)((ceil(log10(num_pid))+1)*sizeof(char))];
        //sprintf(time, "%d", int_time);
        
        
        char cmdline_string[5000000];
        char* command_line = take_cmdline(cmdline, cmdline_string);
        
        //DA CONVERTIRE IN STRINGA
        double cpu_usage=take_cpu_usage_process(buffer_stat);
        //char cpu_usage[50];//(int)((ceil(log10(num_pid))+1)*sizeof(char))];
        //sprintf(cpu_usage, "%.2f", cpu_usage);
        
        /*
        mvwprintw(process_label,row, PID_COLUMN,"%s",pid);
        mvwprintw(process_label,row, USER_COLUMN,"%s",user);
        mvwprintw(process_label,row, PRI_COLUMN,"%s",priority);
        mvwprintw(process_label,row, NI_COLUMN,"%s",nice_value);
        mvwprintw(process_label,row, VIRT_COLUMN,"%s",virt);
        mvwprintw(process_label,row, RES_COLUMN,"%d",res);
        mvwprintw(process_label,row, SHR_COLUMN,"%d",share);
        mvwprintw(process_label,row, S_COLUMN,"%s",status_string);
        mvwprintw(process_label,row, CPU_COLUMN,"%.2f",cpu_usage);
        mvwprintw(process_label,row, TIME_COLUMN,"%d",time);
        mvwprintw(process_label,row, CMD_COLUMN,"%s",command_line);
        
        printf("%s\n",pid);
        printf("%s\n",user);
        printf("%s\n",priority);
        printf("%s\n",nice_value);
        printf("%s\n",virt);
        printf("%d\n",res);
        printf("%d\n",share);
        printf("%s\n",status_string);
        printf("%.2f\n",cpu_usage);
        printf("%d\n",time);
        printf("%s\n",command_line);
        */
        row++;
        //break;
        
    } 
}