#include <stdio.h>
#include <omp.h>
void main(){
 #pragma parallel
 {
 	int i,j;
 	int size = 2;
 	printf("\nThe Required Pattern using Static Assignment is : \n\n");
 
 #pragma omp for schedule(static, size)
 for (i = 0; i < 5; i++){
 	for (j = 0; j < 6; j++){
 		printf("*");
 	}
 	printf("\n");
 }
}
}
