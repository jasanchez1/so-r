#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>


int main(int argc, char const *argv[])
{ 
  bool state = true; // true means green light, otherwise red
  bool alive = true;
  int counter = 0;   //Temporal counter for killing proceses, supr when signals are implemented   
  printf("I'm the SEMAFORO process and my PID is: %i\n", getpid());
  int parent_pid = atoi(argv[2]);
  int delay      = atoi(argv[1]);
  int id         = atoi(argv[0]);
  while(alive){
    sleep(delay);
    state = !state;
    printf("PID: %i Color: %i\n", getpid(), state);
    counter++;
    if (counter ==10){ //supr when done with signals
      alive = false;
    }
  }
}

