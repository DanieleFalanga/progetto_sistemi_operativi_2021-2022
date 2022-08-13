#include "proc_function.h"

char* take_priority(char** buffer){
    return buffer[17];
}

char* take_nice_value(char** buffer){
    return buffer[19];
}

char* take_virt(char** buffer){
    return buffer[22];
}

char* take_status(char** buffer){
    return buffer[2];
}

int take_time(char** buffer){
    int utime = atoi(buffer[14]);
    int stime = atoi(buffer[15]);
    int time = utime + stime;
    return time;
}

char* take_res(char** buffer){
    return buffer[1];
}

char* take_share(char** buffer){
    return buffer[2];
}

char* take_cmdline(char* path, char* string){
    FILE* fptr = fopen(path, "r");
    fgets(string, 70, fptr);
    fclose(fptr);
    return string;
}

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

//Flavio
double take_cpu_usage_process(char** buffer_stat){
    double utime=atof(buffer_stat[13])/sysconf(_SC_CLK_TCK);
    double stime=atof(buffer_stat[14])/sysconf(_SC_CLK_TCK);
    //printf("%f\n", stime);

    double starttime=atof(buffer_stat[21])/sysconf(_SC_CLK_TCK);
    double cpu_usage= (utime+stime)*100/(UPTIME-starttime);
    return cpu_usage;


}








