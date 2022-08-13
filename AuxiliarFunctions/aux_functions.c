#include "aux_function.h"


//Daniele
void strtok_aux(char* path, char* delimiter, char** str_buffer){
    FILE* fptr = fopen(path, "r"); 
    
    char string[2048];

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
            count++;
            token = strtok(NULL, delimiter);
        }
        
    }
    
    fclose(fptr);
    //ritorno il buffer
    return;
}

//Flavio
/*Search the first occurrence of "expression" in the file in path, divided in token
  respect to the delimter "delimiter".
  Return the index of the token in which the occurrence is found*/
int search_first_occurrence(char* path, char* delimiter, char* expression){
    regex_t regex;
    int reti;
    char* str_buffer[BUFFER_SIZE];
    strtok_aux(path, delimiter, str_buffer);
    int counter=0;
    while(1){
        reti=regcomp(&regex, expression, REG_EXTENDED);
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
    return counter;
}

//Flavio
/*Search all occurrences of "expression" in the file path.
  Insert the indices of occurrences in "buffer_indices"*/
void search_all_occurrences(char* path, char* delimiter, char* expression, int* buffer_indices){
    regex_t regex;
    int reti;
    char* str_buffer[BUFFER_SIZE];
    strtok_aux(path, delimiter, str_buffer);
    int i=0;
    int counter=0;
    while(str_buffer[counter]!=NULL){
        reti=regcomp(&regex, expression, REG_EXTENDED);
        if (reti) {
            fprintf(stderr, "Could not compile regex\n");
            exit(1);
        }
        reti = regexec(&regex, str_buffer[counter], 0, NULL, 0);
        if (!reti) {
            //puts("Match");
            buffer_indices[i]=counter;
            counter++;
            i++;
        }
        else if(reti==REG_NOMATCH){
            //puts("No match");
            counter++;
        }
        else {
            regerror(reti, &regex, str_buffer[counter], sizeof(str_buffer[counter]));
            fprintf(stderr, "Regex match failed: %s\n", str_buffer[counter]);
            exit(1);
        }
        regfree(&regex);
    }
}

