#include "Threads/take_system_info.h"
#include "Threads/take_processes_info.h"
#include "Threads/action_handler.h"
#include "Threads/terminal_handler.h"

int counter_row_min = 1;
int NUM_OF_CORES;

//Daniele buonissima parte, Flavio fix sparsi
int main(int argc, char *argv[]){

  // Strutture dati da inizializzare 
  NUM_OF_CORES = take_num_of_cores();
  char* group_buffer[65534];
  take_group_info(group_buffer);  
  char* titolo = "SimilTop di Flavio Volpi e Daniele Falanga";
  int len_titolo = strlen(titolo)/2;
  

  //gestione dei segnali e inizializzazione ncurses

  struct sigaction psig;
  psig.sa_handler = sig_handler;
  sigaction(SIGINT, &psig, NULL);
  sigaction(SIGBUS, &psig, NULL);
  sigaction(SIGSEGV, &psig, NULL);

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
    bkgd(COLOR_PAIR(3));
  }

  //stampo il titolo
  
  attron(A_BOLD);                   //Metto in grassetto il titolo
  attron(COLOR_PAIR(1));            //Lo coloro col primo colore
  mvprintw(0,(COLS/2)-len_titolo,titolo);
  attroff(COLOR_PAIR(1));
  attroff(A_BOLD); 
  refresh();                        //refresh necessario ad ogni azione di stampa sul terminale


  //Strutturo il programma in finestre, ne ha 3

  //creo 3 finestre, 1° finestra è per le info di sistema
  
  WINDOW* system_box = newwin(10,COLS/2-1, 1,0);
  box(system_box,1,0);                          //Stampa i bordi della finestra
  


  //2° finestra è la label dei processi
  
  WINDOW* label = newwin(1, 0, 11,0);
  wbkgd(label,COLOR_PAIR(2));
  print_label_info(label);
  wrefresh(label);


  //3° finestra è il box dei processi
  
  WINDOW* process_box = newwin(0, 0, 12,0);   //primmi due parametri devono essere 0 per 
                                              //non dare numero fisso di righe e colonne
  box(process_box, 0,0);
  scrollok(process_box, TRUE);
  keypad(process_box, TRUE);  // abilita la mappatura della tastiera  

  //4° finestra è mini-terminal
  WINDOW* terminal_box = newwin(10,COLS/2, 1, COLS/2);
  keypad(terminal_box, TRUE);
  box(terminal_box,1,0);                          //Stampa i bordi della finestra


//IL THREAD DEVE CHIAMARE ACTION_HANDLER PER GESTIRE LO SCORRIMENTO DELLE RIGHE DEL PROCESS_BOX.
//PROBABILMENTE ACTION_HANDLER È SBAGLIATO, MA ALMENO IL THREAD LO ODVREBBE CREARE

  //thread per la gestione delle freccette
  struct args* arguments=(struct args*)malloc(sizeof(struct args));
  arguments->process_box=process_box;
  arguments->terminal_box=terminal_box;

  pthread_t thread1;
  int ret=pthread_create(&thread1, NULL, &action_handler, (void*)arguments);
  if(ret!=0) printf("errore nel thread1...\n\n");

  //Ciclo infinito del programma
  for(;;){
      wmove(process_box, 1, 1);
      wclear(process_box);
      
      take_info_system(system_box); //Stampo le info di sistema nel suo box    
      take_processes_info(group_buffer, process_box);
      
      //Una volta fatte le stampe ne faccio il refresh
      box(process_box, 0,0); 
      wnoutrefresh(system_box);
      wnoutrefresh(process_box);  
      doupdate();
      sleep(1);
  }
  
  pthread_cancel(thread1);   //fine thread
  
  return 0;               //Fine del programma 
}
