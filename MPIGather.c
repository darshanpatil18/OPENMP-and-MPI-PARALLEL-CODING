/*
Assume the variable rank contains the process rank and root is 3. What will be stored in array b [ ] on each of four processes if each executes the following code fragment? 
int b [4] = {0 , 0 , 0 , 0}; 
MPI_Gather ( & rank , 1 , MPI_INT , b , 1 , MPI_INT , root ,MPI_COMM_WORLD);
 Hint. The function prototype is as follows: 
int MPI_Gather ( 
void * sendbuf , // pointer to send buffer 
int sendcount , // number of items to send 
MPI_Datatype sendtype , // type of send buffer data 
void * recvbuf , // pointer to receive buffer 
int recvcount , // items to receive per process 
MPI_Datatype recvtype , // type of receive buffer data 
int root , // rank of receiving process 
MPI_Comm comm ) // MPI communicator to use
*/
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
  int size , rank, i, root = 0;
  int b[4] = {0,0,0,0};
  
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Gather(&rank,1,MPI_INT,b,1,MPI_INT,root,MPI_COMM_WORLD);
  
  printf("Processor %d has data: ", rank);
  
  for(i = 0; i<=size; i++){
      printf("%d ",b[i]);
  }
  printf("\n");
  
  MPI_Finalize();
}
