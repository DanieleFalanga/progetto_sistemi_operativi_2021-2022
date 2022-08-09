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
double take_uptime(char* path_memfile){
    double uptime;
    char* uptime_buffer[2] = {};
    strtok_aux(path_memfile, " ", uptime_buffer);
    uptime = atof(uptime_buffer[0]);
    return uptime;
}

//Flavio
int take_num_of_cores(){
    regex_t regex;
    int reti;

    char* path="/proc/stat";
    char* delimiter="\n";
    char* str_buffer[BUFFER_SIZE];
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