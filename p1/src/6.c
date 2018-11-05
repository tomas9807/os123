#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/signal.h>
#include <sys/times.h>

void terminate(int signum){
    double dub;
    struct tms t;
    if ((dub = times(&t)) == -1)
    perror("times() error");
   else {
    printf("process was dubbed %f seconds ago.\n\n",
           ((double) dub));
    printf("            utime           stime\n");
    printf("parent:    %f        %f\n",
           ((double) t.tms_utime),
           ((double) t.tms_stime));
    printf("child:     %f        %f\n",
           ((double) t.tms_cutime),
           ((double) t.tms_cstime));
  }
    exit(1);
}


int main(int argc,char *argv[]){
if (argc==6){



__uid_t uid1 = (__uid_t ) atoi(argv[1]);
size_t  count1 = (size_t )  atoi(argv[2]);
__uid_t uid2 =  (__uid_t )  atoi(argv[3]);
size_t count2 =  (size_t ) atoi(argv[4]);
size_t time_ = (size_t ) atoi(argv[5]);





    if (signal(SIGALRM, terminate)== SIG_ERR){
    perror("no se pudo crear la senal sigalarm");
    exit(1);
    } 

    pid_t pdi_udi1 = fork();

    if (pdi_udi1 > 0 ){ //padre
      pid_t pdi_udi2 = fork(); 

      if (pdi_udi2==0) { //hijo con udi2
       if(setuid(uid2) < 0 ){
           perror("no existe usuario con el valor de udi2 o es root (y se ejecuto sin permisos de root)");
           exit(1);
       }
         for(size_t i=0;i<count2;i++){
             pid_t pdi_fork2 = fork();
             if(pdi_fork2==0){
                 while(1){

                 }
             }
             else if(pdi_fork2 <0){
                 perror("error forking from child udi2");
             }
             }

      }else if(pdi_udi2<0){

          perror("error forking child udi2");

      }else{  //continue padre
            puts("countdown : %zus",)
            alarm(time_);
            pause();

      }

    }
    else if(pdi_udi1==0){ //hijo con udi1
    if(setuid(uid1) < 0 ){
           perror("no existe usuario con el valor de udi1  o es root (y se ejecuto sin permisos de root)");
           exit(1);
       }
         for(size_t i=0;i<count1;i++){
             pid_t pdi_fork1 = fork();
             if(pdi_fork1==0){
                 while(1){

                 }
             }
             else if(pdi_fork1 <0){
                 perror("error forking from child udi1");
             }
             }
    }else{
        perror("error forking child udi1");
    }


   

    


}
else{
    perror("ha ocurrido un error con los parametros, la sintaxis es: ts uid1 count1 uid2 count2 time");
    exit(1);
}


return 0;
}