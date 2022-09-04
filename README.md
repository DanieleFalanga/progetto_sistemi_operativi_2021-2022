# Similtop di Flavio Volpi e Daniele Falanga
Il seguente programma tende ad emulare il famoso programma Htop presente sui sistemi Gnu/Linux

## Prerequisiti
Il programma necessita dell'installazione delle librerie curses. 

### Debian Based
sudo apt install libncurses5-dev libncursesw5-dev 

### Arch-Based
sudo pacman -S ncurses

## Funzionamento

![screen without terminal](https://github.com/DanieleFalanga/progetto_sistemi_operativi_2021-2022/blob/main/Images/Screenshot%20from%202022-09-04%2016-41-57.png) 
![screen with terminal](https://github.com/DanieleFalanga/progetto_sistemi_operativi_2021-2022/blob/main/Images/Screenshot%20from%202022-09-04%2016-43-53.png)

I comandi disponibili sono:

- Freccia **Su** e **Giu** oppure tramite **rotellina del mouse**: Scendo nella lista dei processi
- Freccia **Sinistra**: Apro il terminale integrato all'interno del programma

All'interno del terminale è possibile eseguire i comandi semplicimente digitando il nome del comando seguito dal pid del processo:

- **shutdown** : chiudo il programma
- **exit**: esce dal terminale permettendo di scendere nuovamente tra i processi tramite le frecce o il mouse
- **kill** [pid] : lancia il segnale "SIGTERM" sul processo desiderato
- **suspend** [pid] : lancia il segnale "SIGSTOP" sul processo desiderato 
- **resume** [pid] : lancia il segnale "SIGCONT" sul processo desiderato
- **quit** [pid] : lancia il segnale "SIGQUIT" sul processo desiderato