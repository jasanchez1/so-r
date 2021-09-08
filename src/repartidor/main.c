#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../file_manager/manager.h"

bool s0 =   true;
bool s1 =   true;
bool s2 =   true;
bool move = true;

  void ManageStops(int sig, siginfo_t *siginfo, void *ucontext){
  
  int option = siginfo -> si_value.sival_int;
  if(option == 0){
    s0 = !s0;
  } else if(option == 1){
    s1 = !s1;
  } else{
    s2 = !s2;
  } 
}
  void  EndProcess(int sig){
          //Outputting info in file
        //printf("Finishing gracefully %i\n", getpid());
        exit(0);
  }

  void Move(int sig){
    move = true;
  }

int main(int argc, char const *argv[])
{
  connect_sigaction(SIGUSR1, ManageStops);
  signal(SIGABRT, EndProcess);  
  signal(SIGALRM, Move);
  bool alive = true;                     //supr when signals are working

  int fpid              = atoi(argv[5]); //parent pid
  int r_id              = atoi(argv[4]); //Distance from 'semaforo 0'
  int distance_storage  = atoi(argv[3]); //Distance from 'bodega'
  int distance_2        = atoi(argv[2]) - 1; //Distance from 'semaforo 2'
  int distance_1        = atoi(argv[1]) - 1; //Distance from 'semaforo 1'
  int distance_0        = atoi(argv[0]) - 1; //Distance from 'semaforo 0'
  int position          = 0;             //Current position


  //registering time
  int clock = 0; //handles general time
  int t0 =    0;
  int t1 =    0;
  int t2 =    0;
  int t3 =    0;

  
  
  while(alive){
    if(move){
    clock ++;
    if (position == distance_0 || position == distance_1 || position == distance_2){ //It's in a 'semaforo' should ask for state
      if(move){alarm(1);}
    // This sets the clock as needed for recording time taken from A to B
     if (position == distance_0){
          
          if (s0){
            position++;
            t0 = clock;
          }
        }
        else if(position == distance_1){
          
          if (s1){
            position++;
            t1 = clock;
          }
        }
        else {
          if(s2){
            position++;
            t2 = clock;
          }
          
        }

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
        
        send_signal_with_int(fpid, getpid());
        sleep(3);
        exit(0);

    }
    else {
        
        
        alarm(1);
        position++;
        //printf("Repartor PID: %i just advanced to position: %i\n", getpid(), position);
    }
    move = false;
  }
  }
}