#include "take_processes_info.h"
#include <limits.h>



void print_process_info(WINDOW* process_box, int count, char* pid, char* user, char* priority, char* nice_value, char* virt, char* res, char* share, char* status, char* cpu_usage, char* time, char* cmdline){
    mvwprintw(process_box, count-counter_row_min, PID_COLUMN, pid);
    mvwprintw(process_box, count-counter_row_min, USER_COLUMN, user);
    mvwprintw(process_box, count-counter_row_min, PRI_COLUMN, priority);
    mvwprintw(process_box, count-counter_row_min, NI_COLUMN, nice_value);
    mvwprintw(process_box, count-counter_row_min, VIRT_COLUMN, virt);
    mvwprintw(process_box, count-counter_row_min, RES_COLUMN, res);
    mvwprintw(process_box, count-counter_row_min, SHR_COLUMN, share);
    mvwprintw(process_box, count-counter_row_min, S_COLUMN, status);
    mvwprintw(process_box, count-counter_row_min, CPU_COLUMN, cpu_usage);
    mvwprintw(process_box, count-counter_row_min, TIME_COLUMN, time);
    mvwprintw(process_box, count-counter_row_min, CMD_COLUMN, "");
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
    int x=0;
    int y=0;
    getmaxyx(process_box, y, x);
    int counter_row_max = counter_row_min + y;
    int count = 0;


    while ((procDirent = readdir(proc)) != NULL) {
//        printf("sto analizzando la cartella proc\n");

        //qua sto considerando la singola cartella/file


        //PROVA PER LO SCORRIMENTO DELLA LISTA
        if(count < counter_row_min || count>=counter_row_max){
            count++;
            continue;
        }

        
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
        char* virt = (char*)malloc(sizeof(char)*1000);    //char virt[10]="";
        char* status;
        char* time = (char*)malloc(sizeof(char)*1000);    //char time[10]="";
        char* cpu_usage = (char*)malloc(sizeof(char)*1000);    //char cpu_usage[10]="";
        char* res = (char*)malloc(sizeof(char)*1000);    //char res[10]="";
        char* share = (char*)malloc(sizeof(char)*1000);    //char share[10]="";
        char* user;
        char* cmdline = "";
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
                take_virt(buffer_stat, virt);
                status = take_status(buffer_stat);
                take_time(buffer_stat, time);
                take_cpu_usage_process(buffer_stat, cpu_usage);
            }
            else if (strcmp("statm", proc_pid_Dirent->d_name) == 0){

                strcat(path, directory);
                strcat(path, "/");
                strcat(path, proc_pid_Dirent->d_name);

                strtok_aux(path, " ", buffer_statm);
                take_res(buffer_statm, res);
                take_share(buffer_statm, share);        

            }
            
            else if(strcmp("status", proc_pid_Dirent->d_name) == 0){
                strcat(path, directory);
                strcat(path, "/");
                strcat(path, proc_pid_Dirent->d_name);

                //fai controllo se il processo è un processo o un thread
                char* buffer_status[100000];
                strtok_aux(path, "\t", buffer_status);
                
                if(is_a_process(buffer_status)==0) {
                    is_process=1;
                    int group_id = atoi(buffer_status[18]);
                    user = group_buffer[group_id];
                }
                else{
                    break;
                }
            }/*
            else if(strcmp("cmdline", proc_pid_Dirent->d_name) == 0){
                strcat(path, directory);
                strcat(path, "/");
                strcat(path, proc_pid_Dirent->d_name);

                cmdline = take_cmdline(path);
            }*/
         
        }

        //se è processo stampa, sennò no

/*Consideriamo terminale a schermo intero. Un metodo per stamparli potrebbe essere di contare quante sono le righe della process box (che sono fisse)
  e stampiamo solo le righe che entrano a schermo. Teniamo un contatore che tiene conto della prima riga non letta. Se si preme la freccia in giù una 
  volta, andiamo a cancellare la prima riga con clrtoeol (o una di quelle), e ristampiamo le righe scalandole tutte di una.
*/
        if(is_process==1){
            count++;
            print_process_info(process_box, count, pid, user, priority, nice_value, virt, res, share, status, cpu_usage, time, cmdline);

        }
        free(virt);
        free(share);
        free(res);
        free(cpu_usage);
        free(time);
        closedir(proc_pid);
    }
    // Close directory and exit.
    closedir (proc);
}