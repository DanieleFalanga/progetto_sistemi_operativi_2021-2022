#include "proc_function.h"

//Daniele
char* take_priority(char** buffer){
    return buffer[17];
}

//Daniele
char* take_nice_value(char** buffer){
    return buffer[18];
}

//Daniele
void take_virt(char** buffer, char* str){
    //TODO: da trasfirmare in kB, MB,...
    float num = atof(buffer[22]);
    if(num < 1000000){
        sprintf(str, "%f", num);
    }
    num /= (1024*1024);
    sprintf(str, "%.2fM", num);
}

//Daniele
char* take_status(char** buffer){
    return buffer[2];
}

//Daniele
void take_time(char** buffer, char* str){
    float utime = atof(buffer[13]);
    float stime = atof(buffer[14]);
    float time = utime + stime;
    sprintf(str, "%.3f", time);
}

//Daniele
void take_res(char** buffer, char* str){
    int res = atoi(buffer[1])*4;
    sprintf(str, "%d", res);
}

//Daniele
void take_share(char** buffer, char* str){
    int share = atoi(buffer[2])*4;
    sprintf(str, "%d", share);
}

//Daniele
void take_cmdline(char* path, char* string){
    FILE* fptr = fopen(path, "r");
    
    size_t size = BUFFER_SIZE;
    getline(&string, &size, fptr);

    if(fclose(fptr)!=0)
        fprintf(stderr,"Impossibile chiudere file (cmd), %s\n", path);
    return;
}

//Daniele
int search_group_id(char* path){
    FILE* fptr = fopen(path, "r");

    if(fptr == NULL){
        fprintf(stderr,"Impossibile aprire file (sg) %s\n", path);
        return 1;
    }

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
    if(fptr != 0){
        fprintf(stderr,"Impossibile chiudere file (sg) %s\n", path);
        return 1;
    }
    return group_id;
}



//Flavio
void take_cpu_usage_process(char** buffer_stat, char* str){
    double utime=atof(buffer_stat[13])/sysconf(_SC_CLK_TCK);
    double stime=atof(buffer_stat[14])/sysconf(_SC_CLK_TCK);
    //printf("%f\n", stime);

    double starttime=atof(buffer_stat[21])/sysconf(_SC_CLK_TCK);
    double cpu_usage= (utime+stime)*100/(UPTIME-starttime);
    
    //TODO: approssima a due/tre cifre

    sprintf(str, "%.2lf", cpu_usage);
}




/////////////////////////////////////////////
//Flavio
int is_a_process(char** buffer){
    
    return strcmp(buffer[7],buffer[11]);
}






