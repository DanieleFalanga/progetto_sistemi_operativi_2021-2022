#include "Threads/take_info_system.h"
#include "Threads/take_processes_info.h"


static void fine(int sig); 
void print_label_info(WINDOW* label);


int main(int argc, char *argv[]){
  
  
  /* Strutture dati da inizializzare */ 
  
  char* group_buffer[65534];
  take_group_info(group_buffer);  
  char* titolo = "SimilTop di Flavio Volpi e Daniele Falanga";
  int len_titolo = strlen(titolo)/2;
  

  //gestione dei segnali e inizializzazione ncurses
  
  (void) signal(SIGINT, fine);      /* termina al segnale di interruzione */ 
  (void) signal(SIGBUS, fine);
  (void) signal(SIGSEGV,fine);
  (void) initscr();      /* inizializza la libreria curses */ 
  keypad(stdscr, TRUE);  /* abilita la mappatura della tastiera */ 
  (void) nonl();         /* non convertire NL->CR/NL in output */ 
  (void) cbreak();       /* prende i caratteri in input uno alla volta, senza attendere il \n */ 
  (void) noecho();       /* nessuna echo dell'input */ 
  refresh();
  

  //inizializzo i colori, controllo che il terminale li supporti
  
  if (has_colors()){
    start_color(); //Funzione che attiva i colori
    
    //titolo del pair, utile dopo. 2° Colore delle scritte, 3° Colore di BackGround 
    
    init_pair(1, COLOR_BLACK, COLOR_WHITE); //Colore titolo 
    init_pair(2,COLOR_BLACK, COLOR_CYAN); //Colore Label processi
  }


  //stampo il titolo
  
  attron(A_BOLD);                   //Metto in grassetto il titolo
  attron(COLOR_PAIR(1));            //Lo coloro col primo colore
  mvprintw(0,(COLS/2)-len_titolo,titolo);
  attroff(COLOR_PAIR(1));
  attroff(A_BOLD); 
  refresh();                        //refresh necessario ad ogni azione di stampa sul terminale


  /*Strutturo il programma in finestre, ne ha 3*/

  //creo 3 finestre, 1° finestra è per le info di sistema
  
  WINDOW* system_box = newwin(10,COLS/2, 1,0);
  box(system_box,1,0);                          //Stampa i bordi della finestra
  wrefresh(system_box);                         //Refresh della singola finestra
  


  //2° finestra è la label dei processi
  
  WINDOW* label = newwin(1, COLS, 11,0);
  wbkgd(label,COLOR_PAIR(2));
  print_label_info(label);
  wrefresh(label);


  //3° finestra è il box dei processi
  
  WINDOW* process_box = newwin(LINES, COLS, 12,0);
  box(process_box, 12,0);
  wrefresh(process_box);
  
  
  //Ciclo infinito del programma
  for (;;){
      
      take_info_system(system_box); //Stampo le info di sistema nel suo box    
      
      //take_processes_info(group_buffer, process);
      

      //Una volta fatte le stampe ne faccio il refresh
      
      wrefresh(system_box);
      wrefresh(process_box);  
      
      //sleep(2);
  }
  fine(0);               //Fine del programma 
}


//Funzione di gestione dei segnali
static void fine(int sig) 
{
    endwin();
    if(sig == SIGBUS){
      printf("programm terminated with SIGBUS");
    }
    if(sig == SIGSEGV){
      printf("programm terminated with SIGSEGV");
    }
    
    exit(0);
}

//Funzione di stampa per la label dei processi

void print_label_info(WINDOW* label){
  mvwprintw(label, 0, 3, "PID");     //stampa la stringa alle coordinate che gli vengono passate
  mvwprintw(label, 0, 10, "USER");
  mvwprintw(label, 0, 22, "PRI");
  mvwprintw(label, 0, 27, "NI");
  mvwprintw(label, 0, 32, "VIRT");
  mvwprintw(label, 0, 39, "RES");
  mvwprintw(label, 0, 45, "SHR");
  mvwprintw(label, 0, 52, "S");
  mvwprintw(label, 0, 55, "CPU%");
  mvwprintw(label, 0, 61, "TIME");
  mvwprintw(label, 0, 70, "CMD");
}