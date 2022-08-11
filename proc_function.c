#include "proc_function.h"



int search_group_id(char* path){
    FILE* fptr = fopen(path, "r");

    char string[2048];

    int row = 1; 
    int group_id;
    while(fgets(string, 2048, fptr) != NULL){
        if (row == 9){
            char* token = strtok(string, "\t");
            int column = 0; 
            while(token != NULL){
                    if (column == 1){
                    group_id = atoi(token);
                    break;
                }
                column++;
                token = strtok(NULL, "\t");
            }
            break;
        }
        row++;
    }
    fclose(fptr);
    //printf("%d\n", group_id)    
    return group_id;
}

/*
Auxiliary function that return list of group info in /etc/group, list is a array where cell number correspond to ID group number 
and the corresponding strings the ID group name
Daniele
*/
void take_group_info(char** group_buffer){
    char* path = "/etc/group";
    FILE* fptr = fopen(path, "r");
    char string[2048];
    int i = 0;
    //prendo la riga
    int string_count = 0;
    while(fgets(string, 2048, fptr) != NULL){
        //tokenizzo
        //se la stringa è la numero 0 oppure la numero 2
        char* ID_name = ""; 
        char* token = strtok(string, ":");
        while(token != NULL){
            if(string_count == 0){
                int len = strlen(token);
                ID_name = token;
                //printf("%s\n", ID_name);
                string_count++;
                token = strtok(NULL, ":");
            }
            if(string_count == 2){                
                int ID_number = atoi(token);
                int len = strlen(ID_name);
                //printf("%s\n", ID_name);
                group_buffer[ID_number] = malloc(sizeof(char*) * len + 1);
                strcpy(group_buffer[ID_number], ID_name);
                //printf("%s\n", group_buffer[ID_number]);
                string_count++;
                token = strtok(NULL, ":");

            }
            else{
                string_count++;
                token = strtok(NULL, ":");
            }
        }
        i++;
        string_count = 0;
    }
}



void take_processes_info(){
    

    
    //printf("%s\n", group_buffer[search_group_id("/proc/1152/status")]);
    

    for (int num_pid = 1; num_pid<100000; num_pid++){
        //inizializzo i buffer
        char stat[100] = "/proc/";
        char statm[100] = "/proc/";
        char cmdline[100] = "/proc/";
        char status[100] = "/proc/";
        
        //mi prendo la stringa del pid
        char pid[(int)((ceil(log10(num_pid))+1)*sizeof(char))];
        sprintf(pid, "%d", num_pid);
        
        //faccio la prima strcat per un file
        strcat(stat, pid);
        strcat(stat, "/stat");
        
        //se il file esiste continuo, altrimenti passo all'iterazione successiva
        if(fopen(stat, "r") == NULL)
            continue; 
        
        //faccio le altre strcat
        strcat(stat, pid);
        strcat(stat, "/stat");
        strcat(statm, pid);
        strcat(statm, "/statm");
        strcat(cmdline, pid);
        strcat(cmdline, "/cmdline");
        strcat(status, pid);
        strcat(status, "/status");

        //ti prendi i buffer dei file con strtok_aux

        //chiami le relative funzioni
        break;
        
    } 

}

