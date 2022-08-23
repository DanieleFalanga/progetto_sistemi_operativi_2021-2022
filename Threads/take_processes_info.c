#include "take_processes_info.h"
#include <limits.h>

void print_process_info(WINDOW* process_box, int count, char* pid, char* user, char* priority, char* nice_value, char* virt, char* res, char* share, char* status, char* cpu_usage, char* time, char* cmdline){
    mvwprintw(process_box, count, PID_COLUMN, pid);
    mvwprintw(process_box, count, USER_COLUMN, user);
    mvwprintw(process_box, count, PRI_COLUMN, priority);
    mvwprintw(process_box, count, NI_COLUMN, nice_value);
    mvwprintw(process_box, count, VIRT_COLUMN, virt);
    mvwprintw(process_box, count, RES_COLUMN, res);
    mvwprintw(process_box, count, SHR_COLUMN, share);
    mvwprintw(process_box, count, S_COLUMN, status);
    mvwprintw(process_box, count, CPU_COLUMN, cpu_usage);
    mvwprintw(process_box, count, TIME_COLUMN, time);
    mvwprintw(process_box, count, CMD_COLUMN, "");
}


void take_processes_info(char** group_buffer, WINDOW* process_box){
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
    
//    printf("sto aprendo la directory proc\n");
    // Process each entry.
    //analizzo ogni singolo file/directory nella cartella proc
    int count = 0;
    while ((procDirent = readdir(proc)) != NULL) {
//        printf("sto analizzando la cartella proc\n");


        //qua sto considerando la singola cartella/file
    
        char* end;
        errno=0;
        long val = strtol(procDirent->d_name, &end, 10);
        if(is_regular_file(procDirent->d_name) == 1 ||  end==procDirent->d_name){
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
        char* time;
        char* cpu_usage;
        char* res;
        char* share;
        char* user;
        char cmdline[1000]="";
        char* buffer_statm[BUFFER_SIZE];
        char* buffer_stat[BUFFER_SIZE];   

        char directory[50]="";
        strcat(directory, "/proc/");
        strcat(directory, pid);
        proc_pid = opendir(directory);
        
//        printf("sto aprendo %s\n\n", directory);
        int is_process=-1;
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
                char* buffer_status[BUFFER_SIZE];
                strtok_aux(path, "\t", buffer_status);
                if(is_a_process(buffer_status)==0) {
                    is_process=1;
                    user = group_buffer[search_group_id(path)];
                }
                else{
                    break;
                }
            }
            else if(strcmp("cmdline", proc_pid_Dirent->d_name) == 0){
                strcat(path, directory);
                strcat(path, "/");
                strcat(path, proc_pid_Dirent->d_name);

                take_cmdline(path, cmdline);
            }
         
        }

        //se è processo stampa, sennò no
        if(is_process==1){
/*            printf("\n\nINFO\n");
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
*/
            count++;
            print_process_info(process_box, count, pid, user, priority, nice_value, virt, res, share, status, cpu_usage, time, cmdline);
        }

    }
    // Close directory and exit.
    closedir (proc);
}