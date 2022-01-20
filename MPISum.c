/*
Write a MPI program to calculate the sum of numbers from 1 to 1000 in a parallel fashion while executing on all the cluster nodes and providing the result at the end on only one node. It should be noted that the print statement for the sum is only executed on the node that is ranked zero (O). Also calculate the execution time & wtime and find out environment variables. (Note: You have to use time stamp function to also print the time at begging and end of parallel code segment)
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
        int sum = 0;

        for (i = 0; i < elements_per_process; i++)
            sum += a[i];

        int tmp;

        for (i = 1; i < np; i++) {
            MPI_Recv(&tmp, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            int sender = status.MPI_SOURCE;
            sum += tmp;
        }
        printf("Sum of array is : %d\n", sum);
    }
    else {

        MPI_Recv(&n_elements_recieved, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&a2, n_elements_recieved, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        int partial_sum = 0;

       for (int i = 0; i < n_elements_recieved; i++)
            partial_sum += a2[i];

       MPI_Send(&partial_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
