#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char const *argv[])
{
  printf("I'm the REPARTIDOR process and my PID is: %i\n", getpid());
  bool alive = true;                     //supr when signals are working
  int distance_storage  = atoi(argv[3]); //Distance from 'bodega'
  int distance_2        = atoi(argv[2]); //Distance from 'semaforo 2'
  int distance_1        = atoi(argv[1]); //Distance from 'semaforo 1'
  int distance_0        = atoi(argv[0]); //Distance from 'semaforo 0'
  int position          = 0;             //Current position

  while(alive){

    if (position == distance_0 || position == distance_1 || position == distance_2){ //It's in a 'semaforo' should ask for state
        sleep(3); //Placeholder, should ask for 'semaforo state'
        position++;
        printf("Repartor PID: %i just advanced to position: %i\n", getpid(), position); 
    }
    else if (position == distance_storage){
        printf("Repartor PID: %i just arrived\n", getpid());
        //gets killed
        alive = false;
    }
    else {
        sleep(1); 
        position++;
        printf("Repartor PID: %i just advanced to position: %i\n", getpid(), position);
    }
  }
}