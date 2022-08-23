#include "take_processes_info.h"
#include <limits.h>

void take_processes_info(char** group_buffer, WINDOW* process_label){
    int ret;
    struct dirent *procDirent;
    DIR *proc;
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
    
        char* end;
        errno=0;
        long val = strtol(procDirent->d_name, &end, 10);
        if(is_regular_file(procDirent->d_name) == 1 ||  end==procDirent->d_name){
            count++;
            continue;
        }
//        printf("Non è un file\n");   

        struct dirent *proc_pid_Dirent;
        DIR *proc_pid;
     
        
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
        char cmdline[50]="";
        char* buffer_statm[BUFFER_SIZE];
        char* buffer_stat[BUFFER_SIZE];   

        char directory[50]="";
        strcat(directory, "/proc/");
        strcat(directory, pid);
        proc_pid = opendir(directory);
        
        printf("sto aprendo %s\n\n", directory);
        
        //sto nella cartella proc\[pid], qua dentro mi prendo i valori che mi servono 
        while((proc_pid_Dirent = readdir(proc_pid)) != NULL){
            char path[100]="";

           // printf("%s\n", proc_pid_Dirent->d_name);
            if (strcmp("stat", proc_pid_Dirent->d_name) == 0){
                
                strcat(path, directory);
                strcat(path, "/");
                strcat(path, proc_pid_Dirent->d_name);

                strtok_aux(path, " ", buffer_stat);
                priority = take_priority(buffer_stat);
                nice_value = take_nice_value(buffer_stat);
                virt = take_virt(buffer_stat);
                status = take_status(buffer_stat);
                time = take_time(buffer_stat);
                cpu_usage=take_cpu_usage_process(buffer_stat);
            }
            else if (strcmp("statm", proc_pid_Dirent->d_name) == 0){

                strcat(path, directory);
                strcat(path, "/");
                strcat(path, proc_pid_Dirent->d_name);

                strtok_aux(path, " ", buffer_statm);
                res = take_res(buffer_statm);
                share = take_share(buffer_statm);        

            }
            
            else if(strcmp("status", proc_pid_Dirent->d_name) == 0){
                strcat(path, directory);
                strcat(path, "/");
                strcat(path, proc_pid_Dirent->d_name);

                //fai controllo se il processo è un processo o un thread

                user = group_buffer[search_group_id(path)];

            }
            else if(strcmp("cmdline", proc_pid_Dirent->d_name) == 0){
                strcat(path, directory);
                strcat(path, "/");
                strcat(path, proc_pid_Dirent->d_name);

                take_cmdline(path, cmdline);
 //               printf("%s\n", cmdline);
            }
         
        }

        //se è processo stampa, sennò no
        printf("\n\nINFO\n");
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
        printf("%s\n\n\n",cmdline);
    }
    
    // Close directory and exit.
    closedir (proc);
}