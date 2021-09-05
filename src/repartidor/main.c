#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../file_manager/manager.h"

  void  EndProcess(int sig){
          //Outputting info in file
        printf("Finishin gracefully %i\n", getpid());
        exit(0);
}

int main(int argc, char const *argv[])
{

  
  bool alive = true;                     //supr when signals are working

  int fpid              = atoi(argv[5]); //parent pid
  int r_id              = atoi(argv[4]); //Distance from 'semaforo 0'
  int distance_storage  = atoi(argv[3]); //Distance from 'bodega'
  int distance_2        = atoi(argv[2]); //Distance from 'semaforo 2'
  int distance_1        = atoi(argv[1]); //Distance from 'semaforo 1'
  int distance_0        = atoi(argv[0]); //Distance from 'semaforo 0'
  int position          = 0;             //Current position

  printf("I'm the REPARTIDOR process and my PID is: %i\n  distance_0: %i, disatance_1: %i, distance_2: %i, distance_storage: %i, rid: %i\n", 
          getpid(), 
          distance_storage,
          distance_2,   
          distance_1,   
          distance_0,       
          r_id);

  //registering time
  int clock = 0; //handles general time
  int t0 =    0;
  int t1 =    0;
  int t2 =    0;
  int t3 =    0;

  
  
  while(alive){
    clock ++;
    if (position == distance_0 || position == distance_1 || position == distance_2){ //It's in a 'semaforo' should ask for state

    // This sets the clock as needed for recording time taken from A to B
     if (position == distance_0){
          t0 = clock;
        }
        else if(position == distance_1){
          t1 = clock;
        }
        else {
          t2 = clock;
        }

        clock += 2; //This shouldn't go, it's just to make sense of the sleep(3) bellow line
        sleep(3); //Placeholder, should ask for 'semaforo' state
        position++;
        printf("Repartor PID: %i, ID: %i just advanced to position: %i\n", getpid(), r_id, position);

    }
    else if (position == distance_storage){
        printf("Repartor PID: %i just arrived, fpid: %i\n", getpid(), fpid);

        //Setting arrival clock 
        t3 = clock;

        //Outputting info in file
        char filename[sizeof "./repartidor_x.txt"];
        sprintf(filename, "./repartidor_%i.txt", r_id);
        FILE *fp = fopen(filename, "w");
        fprintf(fp, "%i,%i,%i,%i",t0, t1, t2, t3);
        fclose(fp);

        

        //Literally reports that it wants to be killed
        signal(SIGABRT, EndProcess);
        send_signal_with_int(fpid, getpid());
        sleep(3);

    }
    else {
        sleep(1); 
        position++;
        //printf("Repartor PID: %i just advanced to position: %i\n", getpid(), position);
    }
  }
}