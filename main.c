#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

/* OBIETTIVO: ritornare un array di puntatori a stringhe*/

void strtok_aux(char* path, char* delimiter, char** str_buffer){
    FILE* fptr = fopen(path, "r"); 
    
    char string[2048];

    //char* str_buffer[40] = {}; 

    if(fptr == NULL){
        fprintf(stderr, "Impossibile aprile file %s\n", path);
    }
    //prendo lo stringone
    while (fgets(string, 2048, fptr) != NULL)
    {
        //lo tokenizzo e inserisco in ogni puntatore dell' array la stringa di riferimento
        int count = 0;
        char* token = strtok(string, delimiter);
        while (token != NULL)
        {   
            int len = strlen(token);
            str_buffer[count] = malloc(sizeof(char*) * len + 1);
            strcpy(str_buffer[count], token);
//            printf("%s\n", str_buffer[count]);
            count++;
            token = strtok(NULL, delimiter);
        }
        for(int i=0; i<3; i++)
            printf("%s\n", str_buffer[i]);
        
    }
    
    fclose(fptr);
    //ritorno il buffer
    return;
}

int main(int argc, char** argv){
    char* str_buffer[BUFFER_SIZE] = {};
    strtok_aux("/proc/stat", " ", str_buffer);
    //printf("%s\n", str_buffer[3]);
    return 0;
}

