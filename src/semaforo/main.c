#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include "../file_manager/manager.h"


bool alive = true;
bool shout = false;

void EndProcess(int sig){
  alive = false;
  printf("semaforo killed\n");
}

void SignalChange(int sig){
  shout = true;
}

int main(int argc, char const *argv[])
{ 

  signal(SIGABRT, EndProcess);
  signal(SIGALRM, SignalChange);
  bool state = true; // true means green light, otherwise red

  int counter = 0;   //Temporal counter for killing proceses, supr when signals are implemented   
  
  int parent_pid = atoi(argv[2]) +1;
  int delay      = atoi(argv[1]);
  int id         = atoi(argv[0]);

  printf("I'm the SEMAFORO process and my PID is: %i\n", getpid());
  alarm(delay);
  while(alive){
    
    state = !state;

    if(shout) {
      send_signal_with_int(parent_pid, id);
      alarm(delay);
      shout = !shout;
    }
    
    //printf("PID: %i Color: %i\n", getpid(), state);
    counter++;
    if (!alive){ //supr when done with signals

      //Creating outputfile
      char filename[sizeof "./semaforo_x.txt"];
      sprintf(filename, "./semaforo_%i.txt", id);
      FILE *fp = fopen(filename, "w");
      fprintf(fp, "%i" ,counter);
      fclose(fp);

    }
  }

}

