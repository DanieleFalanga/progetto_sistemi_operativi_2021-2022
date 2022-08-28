#include "Threads/take_system_info.h"
#include "Threads/take_processes_info.h"
#include "Threads/action_handler.h"
#include "Threads/terminal_handler.h"


static void fine(int sig); 
void print_label_info(WINDOW* label);


//int boh(int argc, char *argv[]){
int main(){

  // Strutture dati da inizializzare 
  counter_row_min=12;

  char* group_buffer[65534];
  take_group_info(group_buffer);  
  char* titolo = "SimilTop di Flavio Volpi e Daniele Falanga";
  int len_titolo = strlen(titolo)/2;
  

  //gestione dei segnali e inizializzazione ncurses
  
  (void) signal(SIGINT, fine);      // termina al segnale di interruzione  
  (void) signal(SIGBUS, fine);
  (void) signal(SIGSEGV,fine);
  (void) initscr();      // inizializza la libreria curses 
  (void) nonl();         // non convertire NL->CR/NL in output 
  (void) cbreak();       // prende i caratteri in input uno alla volta, senza attendere il \n  
  (void) noecho();       // nessuna echo dell'input  
  curs_set(0);
  refresh();


  //inizializzo i colori, controllo che il terminale li supporti
  
  if (has_colors()){
    start_color(); //Funzione che attiva i colori
    
    //titolo del pair, utile dopo. 2° Colore delle scritte, 3° Colore di BackGround 
    
    init_pair(1, COLOR_BLACK, COLOR_WHITE); //Colore titolo 
    init_pair(2,COLOR_BLACK, COLOR_GREEN); //Colore Label processi
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
  }
  bkgd(COLOR_PAIR(3));

  //stampo il titolo
  
  attron(A_BOLD);                   //Metto in grassetto il titolo
  attron(COLOR_PAIR(1));            //Lo coloro col primo colore
  mvprintw(0,(COLS/2)-len_titolo,titolo);
  attroff(COLOR_PAIR(1));
  attroff(A_BOLD); 
  refresh();                        //refresh necessario ad ogni azione di stampa sul terminale


  //Strutturo il programma in finestre, ne ha 3

  //creo 3 finestre, 1° finestra è per le info di sistema
  
  WINDOW* system_box = newwin(10,COLS/2, 1,0);
  box(system_box,1,0);                          //Stampa i bordi della finestra
  wrefresh(system_box);                         //Refresh della singola finestra
  


  //2° finestra è la label dei processi
  
  WINDOW* label = newwin(1, 0, 11,0);
  wbkgd(label,COLOR_PAIR(2));
  print_label_info(label);
  wrefresh(label);


  //3° finestra è il box dei processi
  
  WINDOW* process_box = newwin(0, 0, 12,0);   //primmi due parametri devono essere 0 per 
                                              //non dare numero fisso di righe e colonne
  
  box(process_box, 0,0);
  wrefresh(process_box);
  scrollok(process_box, TRUE);
  keypad(process_box, TRUE);  // abilita la mappatura della tastiera  
  wmove(process_box, 1, 1);


  //4° finestra è mini-terminal
  WINDOW* terminal_box = newwin(10,COLS/2, 1, COLS/2);
  box(terminal_box,1,0);                          //Stampa i bordi della finestra
  wrefresh(terminal_box);                         //Refresh della singola finestra


//IL THREAD DEVE CHIAMARE ACTION_HANDLER PER GESTIRE LO SCORRIMENTO DELLE RIGHE DEL PROCESS_BOX.
//PROBABILMENTE ACTION_HANDLER È SBAGLIATO, MA ALMENO IL THREAD LO ODVREBBE CREARE

  //thread per la gestione delle freccette
  pthread_t thread1;
  int ret=pthread_create(&thread1, NULL, &action_handler, process_box);
  if(ret!=0) printf("errore nel thread1...\n\n");

  //thread per la gestione del mini terminale
  //DA AGGIUSTAREB PERCHE STAMPA IN PUNTO SBAGLIATO
  pthread_t thread2;
  ret=pthread_create(&thread2, NULL, &terminal_handler, process_box);
  if(ret!=0) printf("errore nel thread2...\n\n");

  //Ciclo infinito del programma
  for(;;){
      
      take_info_system(system_box); //Stampo le info di sistema nel suo box    

      take_processes_info(group_buffer, process_box);

      //Una volta fatte le stampe ne faccio il refresh
      box(process_box, 0,0); 
      wnoutrefresh(system_box);
      wnoutrefresh(process_box);  
      doupdate();

      wrefresh(system_box);
      wrefresh(process_box);  

      sleep(2);
  }
  pthread_cancel(thread1);   //fine thread
  pthread_cancel(thread2);   //fine thread
  //if(ret) printf("errore nella chiusura del thread\n");
  fine(0);               //Fine del programma 
}


//Funzione di gestione dei segnali
static void fine(int sig) 
{
    
    endwin();
    if(sig == SIGBUS){
      printf("programm terminated with SIGBUS: %d\n", errno);
    }
    if(sig == SIGSEGV){
      printf("programm terminated with SIGSEGV: %d\n", errno);
    }
    
    exit(0);
}

//Funzione di stampa per la label dei processi

void print_label_info(WINDOW* label){
  mvwprintw(label, 0, PID_COLUMN, "PID");     //stampa la stringa alle coordinate che gli vengono passate
  mvwprintw(label, 0, USER_COLUMN, "USER");
  mvwprintw(label, 0, PRI_COLUMN, "PRI");
  mvwprintw(label, 0, NI_COLUMN, "NI");
  mvwprintw(label, 0, VIRT_COLUMN, "VIRT");
  mvwprintw(label, 0, RES_COLUMN, "RES");
  mvwprintw(label, 0, SHR_COLUMN, "SHR");
  mvwprintw(label, 0, S_COLUMN, "S");
  mvwprintw(label, 0, CPU_COLUMN, "CPU%");
  mvwprintw(label, 0, TIME_COLUMN, "TIME");
  mvwprintw(label, 0, CMD_COLUMN, "CMD");
}



//-----MAIN DI PROVA-----//
/*
int main(){
  char* group_buffer[65534];
  take_group_info(group_buffer);
  take_info_system(NULL);
//  take_processes_info(group_buffer, NULL);
//  char* buffer_status[BUFFER_SIZE];
//  strtok_aux("/proc/1/status", "\t", buffer_status);
//  printf("%s    %s\n", buffer_status[7], buffer_status[11]);
}
*/
/*int main(){
   char* group_buffer[65534];
  take_group_info(group_buffer);  
  char* titolo = "SimilTop di Flavio Volpi e Daniele Falanga\n";
  int len_titolo = strlen(titolo)/2;
  

  //gestione dei segnali e inizializzazione ncurses
  
  (void) signal(SIGINT, fine);      // termina al segnale di interruzione  
  (void) signal(SIGBUS, fine);
  //(void) signal(SIGSEGV,fine);
  (void) initscr();      // inizializza la libreria curses 
  clear();
  keypad(stdscr, TRUE);  // abilita la mappatura della tastiera  
  (void) nonl();         // non convertire NL->CR/NL in output 
  (void) cbreak();       // prende i caratteri in input uno alla volta, senza attendere il \n  
  (void) noecho();       // nessuna echo dell'input  
  refresh();
  

  //inizializzo i colori, controllo che il terminale li supporti
  
  if (has_colors()){
    start_color(); //Funzione che attiva i colori
    
    //titolo del pair, utile dopo. 2° Colore delle scritte, 3° Colore di BackGround 
    
    init_pair(1, COLOR_BLACK, COLOR_WHITE); //Colore titolo 
    init_pair(2,COLOR_BLACK, COLOR_GREEN); //Colore Label processi
  }


  //stampo il titolo
  
  attron(A_BOLD);                   //Metto in grassetto il titolo
  attron(COLOR_PAIR(1));            //Lo coloro col primo colore
  //mvprintw(0,(COLS/2)-len_titolo,titolo);
  attroff(COLOR_PAIR(1));
  attroff(A_BOLD); 
  refresh();                        //refresh necessario ad ogni azione di stampa sul terminale


  WINDOW* screen=newpad(0,0);
  wprintw(screen, titolo);
  box(screen, 0, 0);
  prefresh(screen, 0,0,0,0,50, 50);


  WINDOW* system_box=subpad(screen, 10, 10, 1, 1);
  box(system_box, 0, 0);
  prefresh(system_box, 0, 0, 0, 0, 10, 10);
  while(1)
    wgetch(screen);

}*/


