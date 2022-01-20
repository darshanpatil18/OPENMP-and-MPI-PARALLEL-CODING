/*
Write an OpenMP program to find the Max and Min elements in a list of numbers using OpenMPCritical clause to understand: 
Hint: As Max& Min value is easily prone to change by another thread after comparing with Array [Index], the use of ‘critical’ section is highly demanded to execute such computation on one thread at a time.
*/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

int i,max,min;
int size;

printf("Enter the Number of Elements in an Array : ");
scanf("%d",&size);

int a[size];
printf("Enter the Elements of an Array : \n");
for(i = 0; i < size; i++){
	scanf("%d",&a[i]);
}

printf("The Elements are : \n");
for(i = 0; i < size; i++){
	printf_s("%d\n", a[i]);
}
max = a[0];
min = a[0];

#pragma omp parallel for num_threads(4)

for (i = 1; i < size; i++){

	if (a[i] > max){
		#pragma omp critical
		{
			if (a[i] > max)
				max = a[i];
		}
	}
	if (a[i] < min){
		#pragma omp critical
		{
			if (a[i] < min)
				min = a[i];
		}
	}
}
	printf_s("Maximum Element in the Array : %d\n", max);
	printf_s("Minimum Element in the Array : %d\n", min);
}
