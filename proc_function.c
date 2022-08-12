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


double take_cpu_usage_process(char** buffer_stat){
    double utime=atof(buffer_stat[13])/sysconf(_SC_CLK_TCK);
    double stime=atof(buffer_stat[14])/sysconf(_SC_CLK_TCK);
    //printf("%f\n", stime);

    double starttime=atof(buffer_stat[21])/sysconf(_SC_CLK_TCK);
    double cpu_usage= (utime+stime)*100/(UPTIME-starttime);
    return cpu_usage;


}




//General function that takes all processes informations
void take_processes_info(char** group_buffer){
    //printf("%s\n", group_buffer[search_group_id("/proc/1152/status")]);

    for (int num_pid = 1; num_pid<100000; num_pid++){
        //initialize stat string
        char stat[100] = "/proc/";
        
        //take pid string
        char pid[(int)((ceil(log10(num_pid))+1)*sizeof(char))];
        sprintf(pid, "%d", num_pid);
        
        //first strcat, util for sanity check above
        strcat(stat, pid);
        strcat(stat, "/stat");
        
        //Sanity check
        if(fopen(stat, "r") == NULL)
            continue; 
        
        char* buffer_stat[BUFFER_SIZE];
        strtok_aux(stat, " ", buffer_stat);
        
        if (strcmp(buffer_stat[0], buffer_stat[5]) != 0)
            continue;

        //initialize others paths and do other strcat  
        char statm[100] = "/proc/";
        char cmdline[100] = "/proc/";
        char status[100] = "/proc/";
        strcat(statm, pid);
        strcat(statm, "/statm");
        strcat(cmdline, pid);
        strcat(cmdline, "/cmdline");
        strcat(status, pid);
        strcat(status, "/status");
        

        //take buffers with strtok_aux
        //Not necessary for cmdline and status
        
        char* buffer_statm[BUFFER_SIZE];
        
        strtok_aux(statm, " ", buffer_statm);
        
        //take all necessary parameters with the appropriate functions
        char* user = group_buffer[search_group_id(status)];
        char* priority = take_priority(buffer_stat);
        char* nice_value = take_nice_value(buffer_stat);
        char* virt = take_virt(buffer_stat);
        char* res = take_res(buffer_statm);
        char* share = take_share(buffer_statm);
        char* status_string = take_status(buffer_stat);
        int time = take_time(buffer_stat);
        char cmdline_string[70];
        char* command_line = take_cmdline(cmdline, cmdline_string);
        double cpu_usage=take_cpu_usage_process(buffer_stat);
                
        printf("cpu usage:  %lf\n", cpu_usage);
        
        printf("%s\n", pid);
        /*
        printf("%s\n", user);
        printf("%s\n", priority);
        printf("%s\n", nice_value); //errato
        printf("%s\n", virt);
        printf("%s\n", res); //errato
        printf("%s\n", share); //errato
        printf("%s\n", status_string);
        printf("%d\n", time); //errato
        printf("%s\n", command_line);
        */
        
    } 

}

