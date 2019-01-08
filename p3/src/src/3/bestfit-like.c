#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/signal.h>
#include <sys/times.h>

pid_t pids[30];
size_t random_indexes[10];

size_t get_random_index()
{
    return rand() % (29 + 1 - 0) + 0;
}

int check_number_in_list(size_t list[], size_t n)
{
    printf("n: %i \n", (int)n);
    for (int i = 0; i < 10; i++)
    {
        if (list[i] == n)
        {

            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[])
{
    puts("Se creara 30 procesos de prueba \n");
    sleep(2);
    //crear 30 procesos
    for (int i = 0; i < 30; i++)
    {
        pid_t pid = fork();
        if (pid > 0)
        {
            printf("Proceso con PID %i creado \n", (int)pid);
            pids[i] = pid;
        }
        else
        {

            while (1)
            {
            }
        }
    }
    //matar algunos procesos
    puts("\n Ahora se matara 10 procesos de manera aleatoria \n");
    sleep(2);

    for (int i = 0; i < 10; i++)
    {
        size_t r_idx = get_random_index();
        int check = check_number_in_list(random_indexes, r_idx);
        while (check == 0)
        {
            r_idx = get_random_index();
            check = check_number_in_list(random_indexes, r_idx);
        }
        random_indexes[i] = r_idx;
    }

    for (int i = 0; i < 10; i++)
    {
        kill(pids[random_indexes[i]], SIGTERM);
        printf("Proceso con PID %i matado \n", (int)pids[random_indexes[i]]);
    }
}
