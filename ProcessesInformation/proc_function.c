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



//Flavio
double take_cpu_usage_process(char** buffer_stat){
    double utime=atof(buffer_stat[13])/sysconf(_SC_CLK_TCK);
    double stime=atof(buffer_stat[14])/sysconf(_SC_CLK_TCK);
    //printf("%f\n", stime);

    double starttime=atof(buffer_stat[21])/sysconf(_SC_CLK_TCK);
    double cpu_usage= (utime+stime)*100/(UPTIME-starttime);
    return cpu_usage;


}








