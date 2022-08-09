#include "aux_function.h"

void strtok_aux(char* path, char* delimiter, char** str_buffer){
    FILE* fptr = fopen(path, "r"); 
    
    char string[2048];

    //char* str_buffer[40] = {}; 

    if(fptr == NULL){
        fprintf(stderr, "Impossibile aprile file %s\n", path);
    }
    //prendo lo stringone
    int count = 0;
    while (fgets(string, 2048, fptr) != NULL)
    {
        //lo tokenizzo e inserisco in ogni puntatore dell' array la stringa di riferimento
        char* token = strtok(string, delimiter);
        while (token != NULL)
        {   
            int len = strlen(token);
            str_buffer[count] = malloc(sizeof(char*) * len + 1);
            strcpy(str_buffer[count], token);
            //printf("%s\n", str_buffer[count]);
            count++;
            token = strtok(NULL, delimiter);
        }
        
    }
    
    fclose(fptr);
    //ritorno il buffer
    return;
}

float mem_info(char* path_memfile, char** mem_buffer){
    float mem_percentage;
    char* buffer[BUFFER_SIZE] = {};
    
    //ricavo le informazioni sulla memoria
    strtok_aux(path_memfile, " ", buffer);
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
    return mem_percentage;
}