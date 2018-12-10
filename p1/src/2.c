#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <signal.h>
#include <sys/signal.h>
#include <stdlib.h>

void kill_children(int signum)
{

    killpg(getpgrp(), SIGKILL);
}

int main()
{
    puts("escriba 1 para ver el limite de procesos proporcionado por el kernel o 2 para probar bifurcando procesos hasta que el sistema aguante (puede ser lento) \n");
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
            unsigned long cont = 1;
            unsigned long anterior_cont;

            if (signal(SIGINT, kill_children) == SIG_ERR)
            {
                perror("cannot create signal");
                exit(1);
            }

            while (cont)
            {
                anterior_cont = cont;
                pid = fork();
                if (pid == 0)
                {
                    printf("proceso numero %lu creado (mata a todo los procesos con CONTROL-C) \n", cont);
                    while (1)
                    {
                    }
                }
                else if (pid < 0)
                {

                    printf("el numero de procesos maximo que se alcanzo  del usuario %s (uid : %u) es: %lu \n\n", getpwuid(uid)->pw_name, uid, cont);

                    kill(getpgrp(), SIGKILL);
                    exit(0);
                }

                cont++;
                if (anterior_cont > cont)
                {
                    cont = anterior_cont;
                }
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
