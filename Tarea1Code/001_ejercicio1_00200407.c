#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>

int main() {
  //Inicio de ejecucion con proceso padre
  printf("Proceso padre con ID: %d inicia\n", getpid());

  long childpid1=fork(); //Creacion de primer hijo
  if (childpid1==0) {
    printf("Proceso hijo 1 con ID: %d  y con ID de padre:  %d inicia \n", getpid(),getppid());
    exit(0);
  } else {
    long childpid2=fork(); //Creacion de hijo 2 (se creara primero)
    if (childpid2==0) {
      printf("Proceso hijo 2 con ID: %d  y con ID de padre:  %d inicia \n", getpid(),getppid());
      long gchildid1=fork(); //Creacion de nieto1
      if (gchildid1==0) {
        printf("Proceso nieto 1 con ID: %d  y con ID de padre:  %d inicia \n", getpid(),getppid()); //Ejecucion y fin de nieto 1
        exit(0);
      } else {
        long gchildid2=fork(); //Creacion de nieto 2
        if (gchildid2==0) {
          printf("Proceso nieto 2 con ID: %d  y con ID de padre:  %d inicia \n", getpid(),getppid()); //Creacion y ejecucion de nieto2
          exit(0);
        } else {
          //Se espera a que se acabe de ejecutar todos los nietos de hijo 2 para continuar con la ejecucion de hijo 2
          waitpid(gchildid1,NULL,0);
          printf("Proceso nieto 1 con ID: %ld acaba ejecucion!\n", gchildid1);
          waitpid(gchildid2,NULL,0);
          printf("Proceso nieto 2 con ID: %ld acaba ejecucion!\n", gchildid2);
        }
      }
    } else {
      long childpid3=fork(); //Creacion de hijo 3
      if (childpid3==0) {
        printf("Proceso hijo 3 con ID: %d  y con ID de padre:  %d inicia \n", getpid(),getppid());
        exit(0);
      } else {
        //Padre espera que todos los hijos acaben y termina su ejecucion
        waitpid(childpid2,NULL,0);
        printf("Proceso hijo 2 con ID: %ld acaba ejecucion!\n", childpid2);
        waitpid(childpid1,NULL,0);
        printf("Proceso hijo 1 con ID: %ld acaba ejecucion!\n", childpid1);
        waitpid(childpid3,NULL,0);
        printf("Proceso hijo 3 con ID: %ld acaba ejecucion!\n", childpid3);
        printf("Proceso padre con ID: %d acaba ejecucion!\n", getpid());
        exit(0);
      }
    }
  }
}
