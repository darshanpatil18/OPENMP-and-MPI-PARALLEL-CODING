/*
Using OpenMP, Design, develop and run a multi-threaded program to perform and print vector addition.
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

#define row 4

int A[row];
int B[row];
int Sum[row];

int main() 
{
    int i; 
    omp_set_num_threads(omp_get_num_procs());
    
	printf("Enter the Matrix 'A' : \n");
	for (i= 0; i< row; i++){
		scanf("%d", &A[i]);
	}
	
    printf("Enter the Matrix 'B' : \n");
    for (i= 0; i< row; i++)
		scanf("%d", &B[i]);
      
	#pragma omp parallel for private(i) shared(A)
    for (i = 0; i < row; ++i) {    
        Sum[i] += A[i] + B[i];
    }
	
	printf("The Sum Matrix is : \n");
	for (i= 0; i< row; i++)
		printf("%d\n",Sum[i]);
}
