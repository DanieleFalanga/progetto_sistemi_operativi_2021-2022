#include "proc_function.h"

char* take_priority(char** buffer){
    return buffer[17];
}

char* take_nice_value(char** buffer){
    return buffer[18];
}

/*char* take_virt(char** buffer){
    //TODO: da trasfirmare in kB, MB,...
    char str[20];
    float num = atof(buffer[22]);
    if(num < 1000000){
        sprintf(str, "%f", num);
        return str;
    }
    num /= (1024*1024);
    sprintf(str, "%.2fM", num);
    return str;
}
*/
void take_virt(char** buffer, char* str){
    //TODO: da trasfirmare in kB, MB,...
    float num = atof(buffer[22]);
    if(num < 1000000){
        sprintf(str, "%f", num);
    }
    num /= (1024*1024);
    sprintf(str, "%.2fM", num);
}



char* take_status(char** buffer){
    return buffer[2];
}

/*char* take_time(char** buffer){
    int utime = atoi(buffer[13]);
    int stime = atoi(buffer[14]);
    int time = utime + stime;
    //char str[(int)((ceil(log10(time))+1)*sizeof(char))];
    char str[50];
    sprintf(str, "%d", time);

    return str;
}

char* take_res(char** buffer){
    int res = atoi(buffer[1])*4;
    //char str[(int)((ceil(log10(res))+1)*sizeof(char))];
    char str[50];
    sprintf(str, "%d", res);
    return str;
}

char* take_share(char** buffer){
    int share = atoi(buffer[2])*4;
    //char str[(int)((ceil(log10(share))+1)*sizeof(char))];
    char str[50];
    sprintf(str, "%d", share);
    return str;
}
*/
void take_time(char** buffer, char* str){
    float utime = atof(buffer[13]);
    float stime = atof(buffer[14]);
    float time = utime + stime;
    //char str[(int)((ceil(log10(time))+1)*sizeof(char))];
    sprintf(str, "%.3f", time);
}
void take_res(char** buffer, char* str){
    int res = atoi(buffer[1])*4;
    //char str[(int)((ceil(log10(res))+1)*sizeof(char))];
    sprintf(str, "%d", res);
}
void take_share(char** buffer, char* str){
    int share = atoi(buffer[2])*4;
    //char str[(int)((ceil(log10(share))+1)*sizeof(char))];
    sprintf(str, "%d", share);
}





void take_cmdline(char* path, char* string){
    FILE* fptr = fopen(path, "r");
    fgets(string, 1000, fptr);
    if(fclose(fptr)!=0)
        printf("%d\n", errno);
  //  return string;
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
//Flavio
char* take_cpu_usage_process(char** buffer_stat){
    double utime=atof(buffer_stat[13])/sysconf(_SC_CLK_TCK);
    double stime=atof(buffer_stat[14])/sysconf(_SC_CLK_TCK);
    //printf("%f\n", stime);

    double starttime=atof(buffer_stat[21])/sysconf(_SC_CLK_TCK);
    double cpu_usage= (utime+stime)*100/(UPTIME-starttime);
    
    //TODO: approssima a due/tre cifre

    //char str[(int)((ceil(log10(cpu_usage))+1)*sizeof(char))];
    char str[50];
    sprintf(str, "%lf", cpu_usage);
    return str;


}
*/
void take_cpu_usage_process(char** buffer_stat, char* str){
    double utime=atof(buffer_stat[13])/sysconf(_SC_CLK_TCK);
    double stime=atof(buffer_stat[14])/sysconf(_SC_CLK_TCK);
    //printf("%f\n", stime);

    double starttime=atof(buffer_stat[21])/sysconf(_SC_CLK_TCK);
    double cpu_usage= (utime+stime)*100/(UPTIME-starttime);
    
    //TODO: approssima a due/tre cifre

    //char str[(int)((ceil(log10(cpu_usage))+1)*sizeof(char))];
    sprintf(str, "%.2lf", cpu_usage);
}




/////////////////////////////////////////////
int is_a_process(char** buffer){
//    printf("pid: %s\tgpid: %s\n\n", buffer[7], buffer[11]);
    return strcmp(buffer[7],buffer[11]);
}






