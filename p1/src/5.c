#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/signal.h>

int pfd[2];

char const message[] = "recibido";
int cont = 0;
void send_message(int signum){
    
    write(pfd[1],message,sizeof(message));
    size_t c2_pid = getppid() + 2;
    kill(c2_pid, SIGUSR1);

            
}
void print_message(int signum){
  
    char received_message[strlen(message)];
    if(read(pfd[0],received_message,sizeof(message)) > 0 ){
        printf("mensaje: %s ,veces: %i \n",received_message,cont +1 );
        cont++;
    }else{
         perror("waiting message");
    }
    }


int main(int argc,char *argv[]){

pid_t c1,c2;



if (pipe(pfd) < 0 ){
    perror("no se pudo crear el pipe");
    exit(1);
}


c1 = fork();

if (c1==0){ //hijo c1
    perror("child c1 created and running");
    if (signal(SIGALRM, send_message)== SIG_ERR){
    perror("no se pudo crear la senal c1");
    exit(1);
    } 
    
     while (cont<10){
     
     alarm(2);
     pause();
     cont++;
             
     }
     
        
   
    close(pfd[1]);
    exit(0);
}
   


else if (c1 < 0){
    perror("ha ocurrido un error  con c1 ");
    exit(1);
}

else if (c1 > 0 ){ //padre

c2 = fork();

if (c2==0){
  perror("child c2 created and running");
    if (signal(SIGUSR1, print_message)== SIG_ERR){
    perror("no se pudo crear la senal c2 ");
    exit(1);
    } 

    while(cont<10){
        
        pause();
        
    }
    
   
    
    close(pfd[0]);
    exit(0);


}

else if (c2 < 0){
    perror("ha ocurrido un error  con c2 ");
    exit(1);
}



perror("esperando ouput de c2");
wait(NULL);

}








return 0;
}