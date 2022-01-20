/*
Using OpenMP, Design, develop and run a multi-threaded program to perform sum of N elements (N=2021) using Loop work Sharing with schedule clause.
*/
#include <stdio.h>
#include <omp.h>
void main(){
 #pragma parallel
 {
 	int i,sum=0;
 	printf("The Sum Upto N = 2021 is : \n");
 #pragma omp for schedule(dynamic, 1)
 	for (i = 0; i <= 2021; i++){
 		sum=sum + i;
 	}
 	printf("%d",sum);
 }
}
