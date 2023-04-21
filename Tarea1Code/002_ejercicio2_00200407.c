#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc,char *argv[]) {

  if (argc!=3) //Llamada en caso de no tener suficientes argumentos de exec.
  {
    printf("Falta de argumentos, se necesita inputFile y outputFile.\n");
    exit(1);
  }
  int inputFile=open(argv[1], O_RDONLY); //Segundo argumento tiene flag para solo estar en modo lectura
  if (inputFile<0) //Si es menor a 0 hay error
  {
    printf("El archivo esta abierto o existe problema para abrir.\n");
    exit(1);
  }
  int outputFile=open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
  //Modo escritura, se puede crear el archivo en caso de no existir, y en caso de existir se trunca la longitud a 0 para copiar todo de nuevo. CP no hace append.
  if (outputFile<0) {
    printf("El archivo esta abierto o existe problema para abrir.\n");
    exit(1);
  }
  //Variables que tienen los bytes leidos en buffer
  int bytestoRead;
  int bytestoWrite;
  char buffer[4096];
  //MIentras que no exista un EOF, que es 0, se escribe
  while ((bytestoRead=read(inputFile,buffer,4096))>0) {
    bytestoWrite=write(outputFile,buffer,bytestoRead);
    if (bytestoWrite!=bytestoRead) {
      printf("Error de escritura, saliendo de programa!\n");
      exit(1);
    }
  }
  if (bytestoRead<0){
    printf("Error de lectura, saliendo de programa!\n");
    exit(1);
  }

  close(inputFile); //Cierre de archivos
  close(outputFile);
  printf("\nCopia realizada con exito, chequee el archivo %s para ver el nuevo contenido\n",argv[2]);
  exit(0);
}
