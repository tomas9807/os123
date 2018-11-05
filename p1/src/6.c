#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/signal.h>
#include <sys/times.h>

__uid_t type_uid;
__uid_t uid1;
size_t count1;
__uid_t uid2;
size_t count2;

void print_time(int signum)
{
    struct tms t;

    if ((times(&t)) == -1)
    {
        fprintf(stderr, "times() error in %u", type_uid);
        exit(1);
    }

    else
    {
        __uid_t current_uid;
        size_t current_count;

        if (current_uid == 1)
        {
            current_uid = uid1;
            current_count = count1;
        }
        else
        {
            current_uid = uid2;
            current_count = count2;
        }

        printf("%u  %zu %f %f %f \n", current_uid, current_count, (double)t.tms_utime, (double)t.tms_stime, (double)t.tms_stime + (double)t.tms_utime);
        fflush(stdout);
    }
    killpg(getpgrp(), SIGTERM);

    exit(0);
}

int main(int argc, char *argv[])
{
    if (argc == 6)
    {

        uid1 = (__uid_t)atoi(argv[1]);
        count1 = (size_t)atoi(argv[2]);
        uid2 = (__uid_t)atoi(argv[3]);
        count2 = (size_t)atoi(argv[4]);
        size_t time_ = (size_t)atoi(argv[5]);

        pid_t pdi_udi1 = fork();

        if (pdi_udi1 > 0)
        { //padre
            pid_t pdi_udi2 = fork();

            if (pdi_udi2 == 0)
            { //hijo con udi2

                if (setuid(uid2) < 0)
                {
                    perror("no existe usuario con el valor de udi2 o es root (y se ejecuto sin permisos de root)");
                    exit(1);
                }
                pid_t pdi_fork2;
                for (size_t i = 0; i < count2; i++)
                {
                    pdi_fork2 = fork();
                    if (pdi_fork2 == 0)
                    {
                        while (1)
                        {
                        }
                    }

                    else if (pdi_fork2 < 0)
                    {
                        perror("error forking from child udi2");
                    }
                }
               

                type_uid = 2;
                if (signal(SIGUSR1, print_time) == SIG_ERR)
                {
                    perror("no se pdo crear la senal sigalarm");
                    exit(1);
                }

                wait(NULL);
            }
            else if (pdi_udi2 < 0)
            {

                perror("error forking udi2");
            }
            else
            { //continue padre
                puts("  UID  COUNT  USERTIME   SYSTEMTIME   USER+SYSTEM \n\n");
                alarm(time_);
                pause();

                killpg(getpgrp(), SIGUSR1);
            }
        }
        else if (pdi_udi1 == 0)
        { //hijo con udi1

            if (setuid(uid1) < 0)
            {
                perror("no existe usuario con el valor de udi1  o es root (y se ejecuto sin permisos de root)");
                exit(1);
            }

            for (size_t i = 0; i < count1; i++)
            {
                pid_t pdi_fork1 = fork();
                if (pdi_fork1 == 0)
                {

                    while (1)
                    {
                    }
                }

                else if (pdi_fork1 < 0)
                {
                    perror("error forking from child udi2");
                }
            }

            type_uid = 1;
            if (signal(SIGUSR1, print_time) == SIG_ERR)
            {
                perror("no se pudo crear la senal sigalarm");
                exit(1);
            }
            wait(NULL);
        }

        else
        {
            perror("error forking child udi1");
        }
    }
    else
    {
        perror("ha ocurrido un error con los parametros, la sintaxis es: ts uid1 count1 uid2 count2 time");
        exit(1);
    }

    return 0;
}