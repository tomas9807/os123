#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>



unsigned long get_file_size(char const *file_path){
    struct stat sb;
    if (stat(file_path,&sb)){
        perror("no se pudo obtener el tamano del archivo");
        exit(1);
    }
    else{
        return (unsigned long) sb.st_size;
    }
}



int main (int argc, char *argv[]){
    size_t min_buff_size = 1;
    size_t max_buff_size = 16384;

    if (argc!=4){

    perror("Ha ocurrido un error con los parametros ingresados, la sintaxis es: ucp buffersize file1 file2 \n");
    exit(1);

    }
  
    size_t  BUFFSIZE  =  (size_t) atoi(argv[1]);
    char const *FILE1 = argv[2];
    char const *FILE2 = argv[3];
    
    if (!BUFFSIZE || !*FILE1 || !*FILE2){
        perror("Ha ocurrido un error con los parametros ingresados, la sintaxis es: ucp buffersize file1 file2 \n");
       
       fflush(stdout);
        exit(1);
    }
   

    if (BUFFSIZE >= min_buff_size && BUFFSIZE<=max_buff_size){
            unsigned long file_size;
            if (BUFFSIZE > (file_size=get_file_size(FILE1))){
                BUFFSIZE = (size_t) file_size;
            }
        char  BUFFER [BUFFSIZE];

        int fd_file1, fd_file2;
        
        if ((fd_file1=open(FILE1,O_RDONLY))){
        
           
            if( (fd_file2=open(FILE2,O_WRONLY|O_CREAT,0777))){


             if (read(fd_file1,BUFFER,sizeof(BUFFER)) < 0) {
                  perror("ha ocurrido un error al leer el archivo a copiar \n");
                  exit(1);
             }
                
                if (write(fd_file2,BUFFER,sizeof(BUFFER)) < 0){
                    perror("ha ocurrido un error mientras se copiaba el archivo \n");
                    exit(1);
                }
            
            
           

           
            

                
            }
            else{
                
            perror(strcat("Ha ocurrido un error con el segundo archivo ingresado como ->",FILE2));
            exit(1);

            }

         
            
        }
        else{

         perror(strcat(strcat( "Ha ocurrido un error con el primer archivo ingresado como -> ",FILE1),", Es posible que el archivo no exista o no tiene los permisos para leer \n") );
        exit(1);
        }
        int close1 = close(fd_file1);
        int close2 = close(fd_file2);
        if (close1==-1) fprintf(stderr,"error no se pudo cerrar el archivo : %s",FILE1);
        if (close2==-1) fprintf(stderr,"error no se pudo cerrar el archivo : %s",FILE2);
        
    }
    else{
        perror("El buffer excede el rango establecido de 1 a 16384 bytes");
        exit(1);
    }
    return 0;

    
}