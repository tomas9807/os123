#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
int main(int argc,char *argv[]){

if (argc>1){

char const *PROGRAM_PATH = argv[1];
char *parametros[argc -1];
int status;

    for (int i=0;i< argc -2  ;i++){ //cortar(slice) la parte de argv que contiene los parametros para el programa
        parametros[i] = argv[i +2];
    }


pid_t pdi = fork() ;  //crear un proceso hijo para que sea depues reemplazado por el programa a correr
if (pdi<0){
    printf("%s","error fork");
}
else if (pdi==0){  //es hijo
  
   execv(PROGRAM_PATH,parametros);
}
else{ //es padre
   clock_t begin = clock();
   wait(&status);
   clock_t end = clock();
   double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
   printf("the time is: %fs \n",time_spent);
}





}



}