#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/times.h>

char ** get_parametros(int argc,char  **argv){
    int const start_point_parametros = 1;
    if (argc==2) return NULL; //no parameters supplied
  
   
    size_t length_parametros = (argc  - start_point_parametros) + 1;  //+1 cause  will need a space for NULL

    
    char **parametros = (char **)malloc(length_parametros* sizeof(char*));
    perror("allocating memory");
    for (size_t i=0;i<(length_parametros -1 /*-1 for null at the end */);i++) 
        parametros[i] = argv[i + start_point_parametros];
    parametros[length_parametros -1] = NULL; //ensure that last one is null
    
    return parametros;
    

    }

// void print_parametros(char **params){
//     for(int i=0;i<3;i++)
//     printf("param[%i] : %s",i,params[i]);
//     fflush(stdout);
// }  


int main(int argc,char *argv[]){



if (argc>1){


struct tms buf;
long double clktck=sysconf(_SC_CLK_TCK);
char const *prog = argv[1];
char **parametros = get_parametros(argc,argv);
int status;
clock_t proccess_time;


pid_t pdi = fork() ;  //crear un proceso hijo para que sea depues reemplazado por el programa a correr
if (pdi<0){
    puts("error fork");
}
else if (pdi==0){  //es hijo
  
   execv(prog,parametros);
}
else{ //es padre
   if (wait(&status)==-1)  puts("wait error");
   else if (!WIFEXITED(status)) puts("proceso hijo  tuvo un error y no se completo exitosamente :");
   else if((proccess_time=times(&buf))==-1) puts("error al calcular el tiempo del proceso hijo");
   else{
     printf("proceso hijo copiado %Lf seconds ago.\n\n",
           ((long double) proccess_time)/clktck);
    printf("            utime           stime\n");
     printf("parent:    %Lf        %Lf\n",
           ((long double) buf.tms_utime)/clktck,
           ((long double) buf.tms_stime)/clktck);
    printf("child:     %Lf        %Lf\n",
           ((long double) buf.tms_cutime)/clktck,
           ((long double) buf.tms_cstime)/clktck);
   }
   free(parametros);

   
}





}



}