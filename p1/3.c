#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/times.h>
int main(int argc,char *argv[]){



if (argc>1){


struct tms buf;
int tics_per_second = sysconf(_SC_CLK_TCK);
char const *prog = argv[1];
char *parametros[argc -1];
int status;
clock_t proccess_time;




    for (int i=0;i< argc -2  ;i++){ //cortar(slice) la parte de argv que contiene los parametros para el programa
        parametros[i] = argv[i +2];
    }

  
pid_t pdi = fork() ;  //crear un proceso hijo para que sea depues reemplazado por el programa a correr
if (pdi<0){
    puts("error fork");
}
else if (pdi==0){  //es hijo
  if(parametros[3]==NULL) parametros[3]=NULL;
   printf("program: %s, param1: %s,param2: %s,param3: %s and last %s:\n",prog,parametros[0],parametros[1],parametros[2],parametros[3]);
   fflush(stdout);
   char const *perro[] = {"./ucp","20","first.txt","copy2.txt",NULL};
   execv(prog,perro);
}
else{ //es padre
   if (wait(&status)==-1)  puts("wait error");
   else if (!WIFEXITED(status)) puts("proceso hijo  tuvo un error y no se completo exitosamente :");
   else if((proccess_time=times(&buf))==-1) puts("error al calcular el tiempo del proceso hijo");
   else{
    printf("proceso hijo copiado %f seconds ago.\n\n",
           ((double) proccess_time)/tics_per_second);
    printf("            utime           stime\n");
    printf("parent:    %f        %f\n",
           ((double) buf.tms_utime)/tics_per_second,
           ((double) buf.tms_stime)/tics_per_second);
    printf("child:     %f        %f\n",
           ((double) buf.tms_cutime)/tics_per_second,
           ((double) buf.tms_cstime)/tics_per_second);
   }

   
}





}



}