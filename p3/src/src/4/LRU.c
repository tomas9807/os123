#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int const AVOID = -1;

int check_number_in_list(int size_list, int list[size_list], int n)
{

    for (int i = 0; i < size_list; i++)
    {
        if (list[i] == n)
        {

            return 1;
        }
    }
    return 0;
}

int findIndex(int *array, size_t size, int target)
{
    int i = 0;
    while ((i < size) && (array[i] != target))
        i++;

    return (i < size) ? (i) : (-1);
}

void print_line(int size)
{
    printf("\n-");
    for (int column = 0; column < size; column++)
    {
        printf("-----");
    }
}

void print_matrix(int n_row, int n_col, int matrix[n_row][n_col])
{

    int row, column = 0;

    print_line(n_col);
    printf("\n");

    for (row = 0; row < n_row; row++)
    {

        for (column = 0; column < n_col; column++)
        {

            if (column == n_col - 1)
            {
                if (matrix[row][column] < 10)
                {
                    if (matrix[row][column] == AVOID)
                        printf("|    |");
                    else
                        printf("|  %d  |", matrix[row][column]);
                }
                else
                {
                    if (matrix[row][column] == AVOID)
                        printf("|    |");
                    else
                        printf("| %d  |", matrix[row][column]);
                }
            }
            else
            {
                if (matrix[row][column] < 10)
                {
                    if (matrix[row][column] == AVOID)
                        printf("|    ");
                    else
                        printf("|  %d  ", matrix[row][column]);
                }
                else
                {
                    if (matrix[row][column] == AVOID)
                        printf("|   ");
                    else
                        printf("| %d  ", matrix[row][column]);
                }
            }
        }
        print_line(n_col);
        printf("\n");
    }

    getchar();
}

int main(int argc, char *argv[])
{
    int total_frames;
    int total_pages;
    printf("\n Ingrese el numero de frames (bloques) :\t");
    scanf("%d", &total_frames);

    printf("\n Ingrese el numero de paginas que ingresara :\t");
    scanf("%d", &total_pages);

    if (total_frames == 0 || total_pages == 0)
    {
        perror("Se ha ingresado un valor igual a 0");
        exit(1);
    }

    int matrix[total_frames][total_pages];
    for (int i = 0; i < total_frames; i++)
        for (int j = 0; j < total_pages; j++)
            matrix[i][j] = AVOID;
    print_matrix(total_frames, total_pages, matrix);
    int pag;
    int count = 0;

    int faults = 0;
    int used[total_frames];

    int order[total_pages];
    for (int j = 0; j < total_pages; j++)
        order[j] = AVOID;

    for (int i = 0; i < total_pages; i++)
    {
        printf("\n Ingrese la pagina [%i] (numero entero positivo) :\t", i);
        scanf("%d", &pag);
        if (pag < 0)
        {
            perror("numero negativo ingresado");
            exit(1);
        }
        order[i] = pag;
 
        if (count == total_frames) //rebaso chequear numeros
        {

            if (check_number_in_list(total_frames, used, pag) == 0)
            {
                faults++;
                int last_used = order[i - total_frames];
                for(int x= (i - total_frames) + 1;x<i;x++){
                  
                    if (order[x]==last_used){
                        last_used = order[(i - total_frames)-1];
                        break;
                    }
                }
                int idx = findIndex(used, total_frames, last_used);
                used[idx] = pag;

               
            }

            for (int c = 0; c < total_frames; c++)
            {
                matrix[c][i] = used[c];
            }
        }
        else
        {
            if (check_number_in_list(total_frames, used, pag) == 0)
            {
                faults++;

                used[count] = pag;
                order[count] = pag;

                for (int c = 0; c < count; c++)
                {
                    matrix[c][i] = used[c];
                }
                matrix[count][i] = pag;
                count++;
            }
            else
            {
                for (int c = 0; c < count; c++)
                {
                    matrix[c][i] = used[c];
                }
            }
        }
        print_matrix(total_frames, total_pages, matrix);
        printf("Numero de faults %i:\t", faults);
    }
}