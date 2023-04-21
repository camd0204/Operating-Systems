#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(int argc, char **argv) {
    DIR *dirstream;//Apunta a objeto DIR que es un stream de directorio
    struct dirent *direntry;//Apunta a una entrade del directorio objeto dirent
    struct stat fileInfo;//Tipo de objeto stat que da la informacion del archivo

    // Chequeo de path, si no se usa el directorio actual
    char *path;
    if (argc > 1) {
        path = argv[1];
    } else {
        path = ".";
    }


    //eRROR
    if ((dirstream =opendir(path)) == NULL) {
        printf("Error al abrir el directorio. Saliendo.. \n");
        exit(1);//Salida no exitosa
    }

    printf("%-10s %-8s %-8s %s\n", "Permisos", "Dueno", "Size", "Nombre");
    printf("---------- -------- -------- -------------------\n");

    struct passwd *pw;//Objecto que tiene informacion de el usuario
    char permissions[11];//Arreglo de los permisos

    //
    while ((direntry = readdir(dirstream)) != NULL) {
        //Se crea una variable para obtener el nombre del archivo con su path
        char filename[1024];
        //Se usa sprintf para formatear path y el nombre del directorio dentro del nombre del archivo, se pasa a un buffer
        sprintf(filename, "%s/%s", path, direntry->d_name);
        
        if(stat(filename,&fileInfo)==-1){
          printf("Error al obtener info de archivo.Saliendo...\n");
          exit(1);
        }
        
        if((pw=getpwuid(fileInfo.st_uid))==NULL){
          printf("Error al obtener.Saliendo...\n");
          exit(1);
        }

        // Se calcula el tipo de usuario directorio o archivo
        if (S_ISDIR(fileInfo.st_mode)) {
            permissions[0] = 'd';
        } else {
            permissions[0] = '-';
        }
        if (fileInfo.st_mode & S_IRUSR) {//Permisos de usuario
            permissions[1] = 'r';
        } else {
            permissions[1] = '-';
        }
        if (fileInfo.st_mode & S_IWUSR) {
            permissions[2] = 'w';
        } else {
            permissions[2] = '-';
        }
        if (fileInfo.st_mode & S_IXUSR) {
            permissions[3] = 'x';
        } else {
            permissions[3] = '-';
        }
        if (fileInfo.st_mode & S_IRGRP) {//Permisos de grupo
            permissions[4] = 'r';
        } else {
            permissions[4] = '-';
        }
        if (fileInfo.st_mode & S_IWGRP) {
            permissions[5] = 'w';
        } else {
            permissions[5] = '-';
        }
        if (fileInfo.st_mode & S_IXGRP) {
            permissions[6] = 'x';
        } else {
            permissions[6] = '-';
        }
        if (fileInfo.st_mode & S_IROTH) {//Permisos para otros
            permissions[7] = 'r';
        } else {
            permissions[7] = '-';
        }
        if (fileInfo.st_mode & S_IWOTH) {
            permissions[8] = 'w';
        } else {
            permissions[8] = '-';
        }
        if (fileInfo.st_mode & S_IXOTH) {
            permissions[9] = 'x';
        } else {
            permissions[9] = '-';
        }
        permissions[10] = '\0';


        //Impresion de cada archivo incluyendo el path!
        printf("%-10s %-8s %-8lld %s\n", permissions, pw->pw_name, (long long)fileInfo.st_size, filename);
    }

    closedir(dirstream);
    exit(0);
}
