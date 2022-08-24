#include "aux_functions.h"


//Daniele
void strtok_aux(char* path, char* delimiter, char** str_buffer){
    FILE* fptr = fopen(path, "r"); 
    
    char string[2048];

    if(fptr == NULL){
        fprintf(stderr, "Impossibile aprile file %s\n", path);
    }
    //prendo lo stringone
    int count = 0;
    while (fgets(string, 1000000, fptr) != NULL)
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
    
    if(fclose(fptr)!=0) 
        printf("%d\n", errno);
    //ritorno il buffer
    return;
}

//Daniele
/*Uptime in seconds*/
double take_uptime(char* path_memfile){
    double uptime;
    char* uptime_buffer[2] = {};
    strtok_aux(path_memfile, " ", uptime_buffer);
    uptime = atof(uptime_buffer[0]);
    return uptime;
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

//Funzione presa da StackOverflow https://stackoverflow.com/questions/4553012/checking-if-a-file-is-a-directory-or-just-a-file

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}