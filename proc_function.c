#include "proc_function.h"


/*
Funzione ausiliaria per prendere la lista degli ID proprietari dei processi

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
    char* group_buffer[65534];
    take_group_info(group_buffer);
    printf("%s\n", group_buffer[0]);
    printf("%s\n", group_buffer[1000]);
    printf("%s\n", group_buffer[981]);
    
}