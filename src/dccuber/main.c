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
    printf("soy la fabrica\n");
    for (int i= 0; i < 8; i ++){ //make number of 'repartidores' adaptable for input
      sleep(1);                  //make pacing between 'repartidores' adaptable for input
      printf("Clock is: 00:0%d\n", i);
      int repartidor_nuevo = fork();
      if (repartidor_nuevo == 0){
        execlp("./repartidor", "", "", "", (char *)NULL);
  }
    } 
} else {
    int semaforo_1 = fork();
  if (semaforo_1 == 0){
        execlp("./semaforo", "0", "3", str_fpid, (char *)NULL); //Inputs need to be adaptable
  }
  int semaforo_2 = fork();                                  
  if (semaforo_2 == 0){ 
        execlp("./semaforo", "1", "4", str_fpid, (char *)NULL); //Inputs need to be adaptable
  }
  int semaforo_3 = fork(); 
  if (semaforo_3 == 0){                                         
        execlp("./semaforo", "2", "6", str_fpid, (char *)NULL); //Inputs need to be adaptable
  }
}

  printf("Liberando memoria...\n");
  input_file_destroy(data_in);
}
