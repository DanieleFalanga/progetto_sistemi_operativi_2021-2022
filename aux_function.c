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
//Daniele
float take_mem_info(char* path_memfile){
    float mem_percentage;
    char* buffer[BUFFER_SIZE] = {};
    char* mem_buffer[3] = {};
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
int searc_first_occurrence(char* path, char* delimiter, char* expression){
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
void searc_all_occurrences(char* path, char* delimiter, char* expression, int* buffer_indices){
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


//Flavio
int take_num_of_cores(){
    return searc_first_occurrence("/proc/stat", "\n", "intr ") - 1;
}

//Flavio
char* take_num_running_processes(){
    char* path="/proc/stat";
    char* str_buffer[BUFFER_SIZE];
    char* delimiter=" ";
    strtok_aux(path, delimiter, str_buffer);

    return str_buffer[1292];
}
//Flavio
char* take_num_blocked_processes(){
    char* path="/proc/stat";
    char* str_buffer[BUFFER_SIZE];
    char* delimiter=" ";
    strtok_aux(path, delimiter, str_buffer);

    return str_buffer[1294];
}

//Flavio
/*Caluclate percentages of usage of every single core.
  Insert percentages in a buffer */
void take_cores_usage_percentages(float* percentages){
    char* path="/proc/stat";
    char* delimiter=" ";
    char* str_buffer[BUFFER_SIZE];
    strtok_aux(path, delimiter, str_buffer);
    int counter=0;
    for(int i=12; i<167; i+=11){
        float user_time=atof(str_buffer[i]);        //TODO: controllare i valori che stampa
        percentages[counter]=user_time;             //TODO: mancano da calcolare le percentuali
    }                                                 

}