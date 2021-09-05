#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "../file_manager/manager.h"


char* InttoString(int n){
  char* str_int;
  if (n != 0){
    int ENOUGH = ((ceil(log10(n))+1)*sizeof(char)); //To make just enough space for the array
    str_int = malloc(ENOUGH);
  } else {
    str_int = malloc(1*sizeof(char));
  }
  sprintf(str_int, "%d", n);
  return str_int;
}

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

  }
  printf("\n");

  printf("\t- ");
  for (int i = 0; i < 5; i++)
  {
    printf("%s, ", data_in->lines[1][i]);

  }
  printf("\n");

//Setting variables from input data

//Distances          
char *distance_storage = data_in->lines[0][3];
char *distance_2 =       data_in->lines[0][2];
char *distance_1 =       data_in->lines[0][1];
char *distance_0 =       data_in->lines[0][0];

//Timming lines
int pacing =             atoi(data_in->lines[1][0]);
int delivery =           atoi(data_in->lines[1][1]);     

char* delay_0 =          data_in->lines[1][2]; 
char* delay_1 =          data_in->lines[1][3];
char* delay_2 =          data_in->lines[1][4];

//Unique id's
char* id_0    =          "0";
char* id_1    =          "1";
char* id_2    =          "2";

int fabrica;
fabrica = fork(); //fabrica

char* str_fpid = InttoString(getpid());

if (!fabrica){
  int pid[delivery];

    printf("soy la fabrica\n");
    for (int i= 0; i < delivery; i ++){ 
      sleep(pacing);                       
      
      int repartidor_nuevo = fork();
      pid[i] = getpid(); //Saves 'repartidores pid'
      if (repartidor_nuevo == 0){
        execlp(
        "./repartidor", 
        distance_0, 
        distance_1, 
        distance_2, 
        distance_storage,
        InttoString(i),
        (char *)NULL
        );
    }
  } 
} else {
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
