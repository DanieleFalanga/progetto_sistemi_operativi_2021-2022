#include "take_processes_info.h"

void take_processes_info(char** group_buffer, WINDOW* process_label){
    int ret;
    struct dirent *procDirent;
    DIR *proc;
    struct dirent *proc_pid_Dirent;
    DIR *proc_pid;
    // Ensure we can open directory.
    proc = opendir ("/proc");
    
    if (proc == NULL) {
        //routine di chiusura del programma
        //impossibile aprire la cartella proc
        return;
    }
    
    printf("sto aprendo la directory proc\n");
    // Process each entry.
    //analizzo ogni singolo file/directory nella cartella proc
    int count = 0;
    while ((procDirent = readdir(proc)) != NULL) {
        printf("sto analizzando la cartella proc\n");
            
        //qua sto considerando la singola cartella/file
        if(is_regular_file(procDirent->d_name) == 1 || count == 0 || count == 1){        
            count++;
            continue;
        }
        printf("Non è un file\n");        
        
        char* pid =procDirent->d_name;
        char* priority;
        char* nice_value; 
        char* virt;
        char* status;
        int time;
        double cpu_usage;
        int res;
        int share;
        char* user;
        char* cmdline;
        char* buffer_statm[BUFFER_SIZE];
        char* buffer_stat[BUFFER_SIZE];    
        proc_pid = opendir(pid);
        
        printf("sto aprendo %s\n", pid);
        
        //sto nella cartella proc\[pid], qua dentro mi prendo i valori che mi servono 
        while((proc_pid_Dirent = readdir(proc_pid)) != NULL){
            
            if (strcmp("stat", proc_pid_Dirent->d_name)){
                
                strtok_aux(proc_pid_Dirent->d_name, " ", buffer_stat);
                priority = take_priority(buffer_stat);
                nice_value = take_nice_value(buffer_stat);
                virt = take_virt(buffer_stat);
                status = take_status(buffer_stat);
                time = take_time(buffer_stat);
                cpu_usage=take_cpu_usage_process(buffer_stat);
            
            }
            if (strcmp("statm", proc_pid_Dirent->d_name)){
                
                strtok_aux(proc_pid_Dirent->d_name, " ", buffer_statm);
                res = take_res(buffer_statm);
                share = take_share(buffer_statm);        
            
            }
            
            if(strcmp("status", proc_pid_Dirent->d_name)){
                
                user = group_buffer[search_group_id(proc_pid_Dirent->d_name)];
            
            }
            if(strcmp("cmdline", proc_pid_Dirent->d_name)){

                take_cmdline(proc_pid_Dirent->d_name, cmdline);

            }

        }

        printf("%s\n",pid);
        printf("%s\n",user);
        printf("%s\n",priority);
        printf("%s\n",nice_value);
        printf("%s\n",virt);
        printf("%d\n",res);
        printf("%d\n",share);
        printf("%s\n",status);
        printf("%.2f\n",cpu_usage);
        printf("%d\n",time);
        printf("%s\n",cmdline);
    }
    
    // Close directory and exit.
    closedir (proc);
}