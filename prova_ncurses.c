#include <ncurses.h>
#include <stdio.h>


/*questa funzione deve stampare la riga "PID - USER - PRI - NI - ..."
  evidenziata in verde e scritta in nero (i colori si possono anche cambiare ovviamente)
  Il problema è che la riga deve essere una stringa sola per problemi dell'evidenziatura,
  quindi non è possibile fare tante "mvprintw" specificandogli le coordinate, ma dobbiamo
  scegliere le coordinate contando gli spazi da mettere tra le varie parole PID-USER-...
  Scelti gli spazi (e quindi le coordinate di ogni colonna di informazioni), 
  quando metteremo i dati specifici dobbiamo stare attenerci a quelle coordinate

  So che è un po' scomoda, ma per ora è l'unico modo che ho trovato per sottolineare colorato e non bianco-nero 

*/
void create_label_information(){
    attron(COLOR_PAIR(2));      //attiva attributo COLOR_PAIR
    move(10,0);         //vado col cursore a riga:10 colonna:0
    chgat(-1, COLOR_PAIR(2) | A_REVERSE, 0, NULL);      //permette di evidenziare tutta la riga da dove si 
                                                        //trova il cursore con i colori di PAIR
   
   
    mvprintw(10, 3, "PID");     //stampa la stringa alle coordinate che gli vengono passate
    
    mvprintw(10, 10, "USER");
    
    mvprintw(10, 22, "PRI");
    
    mvprintw(10, 27, "NI");
    
    mvprintw(10, 32, "VIRT");
    
    mvprintw(10, 39, "RES");
    
    mvprintw(10, 45, "SHR");
    
    mvprintw(10, 52, "S");
    
    mvprintw(10, 55, "CPU%");
    
    mvprintw(10, 61, "TIME");
    
    mvprintw(10, 70, "CMD");
    
    attroff(COLOR_PAIR(2));     //disattiva l'attributo
    mvprintw(11, 4, "100");
    move(0,0);                  //fa tornare il cursore a coordinate (0,0)

}


void print_process_information(){
    WINDOW* menu_win;
    int highlight=1;


    //start ncurses source
    initscr();
   	start_color();			                     //- Start color functionality
	  init_pair(2, COLOR_BLACK, COLOR_GREEN);  //- attiva l'attributo COLOR_PAIR, che ha come coppia i colori NERO e VERDE, 
                                             //  e associa la coppia al numero 2
                                             //  3 argomenti: -numero associato alla coppia
                                             //               -primo colore è lo sfondo
                                             //               -secondo colore è la scritta


    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    refresh();    
  //  attron(A_REVERSE | PAIR_NUMBER(5));                                    //evidenzia la stringa sottostante
  	
    create_label_information();
    
    
 	getch();		                                      // Wait for user input 
	endwin();
}

int main(){
    print_process_information();

}
