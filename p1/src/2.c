#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <signal.h>
#include <sys/signal.h>
#include <stdlib.h>

int main()
{
    puts("escriba 1 para ver el limite de procesos proporcionado por el kernel o 2 para probar bifurcando procesos hasta que no se reciba mas pids \n");
    int c;
    puts("ingrese 1 o 2 : ");
     
    scanf("%d", &c);
  
    if (c == 1 || c == 2)
    {
        __uid_t uid = getuid();

        if (c == 1)
        {
            struct rlimit limit;
            getrlimit(RLIMIT_NPROC, &limit);

            printf("el limite de procesos activos del usuario %s (uid : %u) es: %u \n\n", getpwuid(uid)->pw_name, uid, (unsigned int)limit.rlim_max);
        }
        else
        {
            __pid_t pid;
            size_t cont = 1;

            while (cont)
            {
                pid = fork();
                if (pid == 0)
                {
                    fprintf("process created %zu",cont);
                    while (1)
                    {
                    }
                }
                else if (pid < 0)
                {

                    printf("el numero de procesos maximo que se alcanzo  del usuario %s (uid : %u) es: %zu \n\n", getpwuid(uid)->pw_name, uid, cont);
                    
                    kill(getpgrp(), SIGKILL);
                    exit(0);
                }
                cont++;
            }
        }
    }
    else
    {
        perror("valor incorrecto");
        exit(1);
    }
    return 0;
}
