#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>



void print_str(int fd,char const *string){
    int length_str = (int) strlen(string);
    for (int i=0;i<=length_str;i++){
        write(fd,&string[i],sizeof(char));
    }
    write(STDOUT_FILENO,"\n",sizeof(char));
}



int main (int argc, char *argv[]){
    
    if (argc!=4){

    print_str(STDERR_FILENO,"Ha ocurrido un error con los parametros ingresados, la sintaxis es: ucp buffersize file1 file2 \n");
    exit(1);

    }
  
    int const BUFFSIZE  =  atoi(argv[1]);
    char const *FILE1 = argv[2];
    char const *FILE2 = argv[3];
    
    if (!BUFFSIZE || !*FILE1 || !*FILE2){
        print_str(STDERR_FILENO,"Ha ocurrido un error con los parametros ingresados, la sintaxis es: ucp buffersize file1 file2");
       
       fflush(stdout);
        exit(1);
    }
   

    if (BUFFSIZE>1 && BUFFSIZE<16384){

        char  BUFFER [BUFFSIZE];

        int fd_file1, fd_file2;
        
        if ((fd_file1=open(FILE1,O_RDONLY)) == -1){
            if( (fd_file2=open(FILE2,O_WRONLY|O_CREAT,0777)) ==-1 ){


             if (read(fd_file1,BUFFER,sizeof(BUFFER)) < 0) {
                  print_str(STDERR_FILENO,"ha ocurrido un error al leer el archivo a copiar");
                  exit(1);
             }
                
                if (write(fd_file2,BUFFER,sizeof(BUFFER)) < 0){
                    print_str(STDERR_FILENO,"ha ocurrido un error mientras se copiaba el archivo");
                    exit(1);
                }
            
            
           

           
            

                
            }
            else{
                
            print_str(STDERR_FILENO,strcat("Ha ocurrido un error con el segundo archivo ingresado como ->",FILE2));
            exit(1);

            }

         
            
        }
        else{

        print_str( STDERR_FILENO,strcat(strcat( "Ha ocurrido un error con el primer archivo ingresado como -> ",FILE1),", Es posible que el archivo no exista o no tiene los permisos para leer") );
        exit(1);
        }
        int close1 = close(fd_file1);
        int close2 = close(fd_file2);
        if (close1==-1) fprintf(stderr,"error no se pudo cerrar el archivo : %s",FILE1);
        if (close2==-1) fprintf(stderr,"error no se pudo cerrar el archivo : %s",FILE2);
        
    }
    else{
        print_str(STDERR_FILENO,"El buffer excede el rango establecido de 1 a 16384 bytes");
        exit(1);
    }
    return 0;

    
}