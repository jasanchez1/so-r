#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "../file_manager/manager.h"

int main(int argc, char const *argv[])
{

  printf("I'm the DCCUBER process and my PID is: %i\n", getpid());

  char *filename = "input.txt";
  InputFile *data_in = read_file(filename);

  printf("Leyendo el archivo %s...\n", filename);
  printf("- Lineas en archivo: %i\n", data_in->len);
  printf("- Contenido del archivo:\n");

  printf("\t- ");
  for (int i = 0; i < 4; i++)
  {
    printf("%s, ", data_in->lines[0][i]);
    //printf(split_by_sep(data_in->lines[0][i], "-"));
  }
  printf("\n");

  printf("\t- ");
  for (int i = 0; i < 5; i++)
  {
    printf("%s, ", data_in->lines[1][i]);
    //printf(split_by_sep(data_in->lines[1][i]));
  }
  printf("\n");


int fabrica;
fabrica = fork(); //fabrica

int fpid = getpid();
int ENOUGH = ((ceil(log10(fpid))+1)*sizeof(char)); //To make just enough space for the array
char str_fpid[ENOUGH];
sprintf(str_fpid, "%d", fpid);

if (!fabrica){
  int alive =               8;  //make number of 'repartidores' adaptable for input
  int pacing =              1;  //make pacing between 'repartidores' adaptable for input                
  char *distance_storage = "9"; //make pacing between 'ds' adaptable for input
  char *distance_2 =       "5"; //make pacing between 'd2' adaptable for input
  char *distance_1 =       "3"; //make pacing between 'd1' adaptable for input
  char *distance_0 =       "2"; //make pacing between 'd0' adaptable for input

  int pid[alive];


    printf("soy la fabrica\n");
    for (int i= 0; i < alive; i ++){ 
      sleep(pacing);                       
      
      int repartidor_nuevo = fork();
      pid[i] = getpid();
      if (repartidor_nuevo == 0){
        execlp(
        "./repartidor", 
        distance_0, 
        distance_1, 
        distance_2, 
        distance_storage, 
        (char *)NULL
        );
  }
    } 
} else {

  char* delay_0 = "3"; //Delays inputs need to be adaptable
  char* delay_1 = "3";
  char* delay_2 = "3";

  char* id_0    = "0";
  char* id_1    = "1";
  char* id_2    = "2";
  
  int semaforo_0 = fork();
  if (semaforo_0 == 0){
  //Creating 'semaforo_0'
        execlp(
          "./semaforo", 
          id_0, 
          delay_0, 
          str_fpid, 
          (char *)NULL
        ); 
  }
  int semaforo_1 = fork();                                  
  if (semaforo_1 == 0){ 
  //Creating 'semaforo_1'
        execlp(
          "./semaforo", 
          id_1, 
          delay_1, 
          str_fpid, 
          (char *)NULL
        ); 
  }
  int semaforo_2 = fork(); 
  if (semaforo_2 == 0){                                         
  //Creating 'semaforo_2'
        execlp(
          "./semaforo", 
          id_2, 
          delay_2, 
          str_fpid, 
          (char *)NULL
        ); 
  }
}

  printf("Liberando memoria...\n");
  input_file_destroy(data_in);
}
