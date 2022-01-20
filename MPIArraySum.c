/*
Write a MPI Program to perform: sending of arrays and simultaneous send and receive by array on each process is created, initialize it on process 0. Once the array has been initialized on process 0, then it is sent out to each process. Also calculate the execution time and time and find out environment variables.
*/
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define n 10

int a[] = { 15, 13, 2, 45, 75, 96, 71, 85, 93, 1 };
int a2[1000];

int main(int argc, char* argv[]){

    int pid, np, elements_per_process, n_elements_recieved;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

  if (pid == 0) {

        int index, i;

        elements_per_process = n / np;
        if (np > 1) {

            for (i = 1; i < np - 1; i++) {
                index = i * elements_per_process;
                MPI_Send(&elements_per_process,1, MPI_INT, i, 0,MPI_COMM_WORLD);
                MPI_Send(&a[index], elements_per_process, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
            index = i * elements_per_process;
            int elements_left = n - index;

            MPI_Send(&elements_left, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&a[index], elements_left, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        int mult = 1;

        for (i = 0; i < elements_per_process; i++)
            mult *= a[i];

        int tmp;

        for (i = 1; i < np; i++) {
            MPI_Recv(&tmp, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            int sender = status.MPI_SOURCE;
            mult *= tmp;
        }
        printf("Multiplication of Array is : %d\n", mult);
    }
    else {

        MPI_Recv(&n_elements_recieved, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&a2, n_elements_recieved, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        int partial_mult = 1;

       for (int i = 0; i < n_elements_recieved; i++)
            partial_mult *= a2[i];

       MPI_Send(&partial_mult, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
