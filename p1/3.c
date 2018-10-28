#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char *argv[]){
printf("%s,%s,%s,%s \n",argv[1],argv[2],argv[3],argv[4]);
if (argc>1){

char const *PROGRAM_PATH = argv[1];
char *parametros[argc -2 ];

    for (int i=0;i< argc -2  ;i++){ //cortar(slice) la parte de argv que contiene los parametros para el programa
        parametros[i] = argv[i +2];
    }

pid_t pdi = execvp(PROGRAM_PATH,parametros);
printf("pdi : %i, program: %s  params : %s,%s,%s \n",pdi,PROGRAM_PATH,parametros[0],parametros[1],parametros[2]);
    


}



}