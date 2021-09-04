#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>


int main(int argc, char const *argv[])
{
  printf("I'm the SEMAFORO process and my PID is: %i\n", getpid());
  int parent_pid = atoi(argv[2]);
  int delay      = atoi(argv[1]);
  int id         = atoi(argv[0]);

  
}

