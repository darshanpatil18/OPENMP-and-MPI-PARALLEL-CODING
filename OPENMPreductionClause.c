/*
Write a simple OpenMP program to employ a ‘reduction’ clause to express the reduction of a for loop. In order to specify the reduction in OpenMP, we must provide 
1. An operation (+ / * / o) 
2. A reduction variable (sum / product / reduction). This variable holds the result of the computation.
*/
#include <stdio.h>
#include <omp.h>
void main(){
	int arr[10] = {10,20,30,90,40,50,70,60,80,100}, i , sum=0;

	printf("Array Elements are : \n");
	for(i=0;i<10;i++){
		printf("%d \n", arr[i]);
	}
	#pragma omp parallel shared(arr) reduction(+: sum)
	{
	#pragma omp for
		for(i = 0; i < 10; i++){
			sum += arr[i];
		}
	printf("Sum of Elements are = %d\n", sum);
	}
printf("Total Sum is = %d\n",sum);
}
