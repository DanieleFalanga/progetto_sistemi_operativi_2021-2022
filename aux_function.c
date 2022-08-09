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
            printf("%s\n", str_buffer[count]);
            count++;
            token = strtok(NULL, delimiter);
        }
        
    }
    
    fclose(fptr);
    //ritorno il buffer
    return;
}