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
 //           printf("%s\n", str_buffer[count]);
            count++;
            token = strtok(NULL, delimiter);
        }
        
    }
    
    fclose(fptr);
    //ritorno il buffer
    return;
}



int take_num_of_cores(){
    regex_t regex;
    int reti;

    char* path="/proc/stat";
    char* delimiter="\n";
    char* str_buffer[5096];
    strtok_aux(path, delimiter, str_buffer);
    int counter=0;
    while(1){
        reti=regcomp(&regex, "intr ", REG_EXTENDED);
        if (reti) {
            fprintf(stderr, "Could not compile regex\n");
            exit(1);
        }
        reti = regexec(&regex, str_buffer[counter], 0, NULL, 0);
        if (!reti) {
 //           puts("Match");
            break;
        }
        else if(reti==REG_NOMATCH){
 //           puts("No match");
            counter++;
        }
        else {
            regerror(reti, &regex, str_buffer[counter], sizeof(str_buffer[counter]));
            fprintf(stderr, "Regex match failed: %s\n", str_buffer[counter]);
            exit(1);
        }
        regfree(&regex);
    }
    return counter-1;
}