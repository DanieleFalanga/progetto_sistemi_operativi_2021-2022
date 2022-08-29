#include "terminal_handler.h"

void* terminal_handler(void* arg){
    WINDOW* terminal_box=(WINDOW*) arg;
    (void) nocbreak();
    keypad(terminal_box, TRUE);
restart:     
    wclear(terminal_box);   
    wmove(terminal_box, 1, 0);
 //   wrefresh(terminal_box);

 //   waddstr(terminal_box, "\n");
    waddstr(terminal_box, "Digita comando che vuoi eseguire seguito dal pid del processo (oppure exit per uscire):\n\n");
    //box(terminal_box, 0,0);
    wrefresh(terminal_box);
    echo();
    curs_set(1);
    char* str;
    int counter=0;
    
    do{
        int c=wgetch(terminal_box);

        if(c==10){                      //è il tasto ENTER
            str = (char*)malloc(sizeof(char)*counter);
            int row, cols;
            getyx(terminal_box, row, cols);
            wmove(terminal_box, row-1, 0);
            int num=winnstr(terminal_box, str, counter);
            waddstr(terminal_box, "\n");
            wrefresh(terminal_box);

            //sleep(5);
            break;
        }
        counter++;

        wrefresh(terminal_box);
    }while(1);


 //   int ret=wgetstr(terminal_box, str);




    wrefresh(terminal_box);
    waddstr(terminal_box, "sto qui\n");
    wrefresh(terminal_box);
    noecho();
  //  waddstr(terminal_box, str);
  //  wrefresh(terminal_box);

    char* command = strtok(str, " ");
    if(strcmp(QUIT, command)==0){
        pid_t pid = atoi(strtok(NULL, " "));
        int ret= kill(pid, SIGQUIT);
        if(ret==-1) 
            waddstr(terminal_box, "signal send... error\n");
            wrefresh(terminal_box);

    }
    else if(strcmp(RESUME, command)==0){
        pid_t pid = atoi(strtok(NULL, " "));
        int ret= kill(pid, SIGCONT);
        if(ret==-1) 
            waddstr(terminal_box, "signal send... error\n");
            wrefresh(terminal_box);

    }
    else if(strcmp(KILL, command)==0){
        pid_t pid = atoi(strtok(NULL, " "));
       int ret=kill(pid, SIGKILL);
       if(ret==-1) 
            waddstr(terminal_box, "signal send... error\n");
            wrefresh(terminal_box);

    }
    else if(strcmp(SUSPEND, command)==0){
        pid_t pid = atoi(strtok(NULL, " "));
        int ret= kill(pid, SIGSTOP);
        if(ret==-1) 
            waddstr(terminal_box, "signal send... error\n");
            wrefresh(terminal_box);

    }
    else if(strcmp(EXIT, command)==0){
        waddstr(terminal_box, "Uscita dal terminale\n");
        wrefresh(terminal_box);
    }
    else{
        waddstr(terminal_box, "Comando non supportato. Attendere un momento...");
        wrefresh(terminal_box);
        sleep(1);
        goto restart;
    }
    
//    mvwaddstr(terminal_box, row+1, 1, "eccomi\n");
    
    
//    waddstr(terminal_box, "sto uscendo\n");

    wrefresh(terminal_box);

    //curs_set(0);
}