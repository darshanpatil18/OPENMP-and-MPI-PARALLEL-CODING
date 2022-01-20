/*
Write a simple OpenMP program to demonstrate Arithmetic Operation using Section Clause.
*/
#include<stdio.h>
#include<omp.h>
void main(){
 int num1,threadNum,num2;
 
 printf("\n Enter First Number : ");
 scanf("%d", &num1);
 printf("\n Enter Second Number : ");
 scanf("%d", &num2);

 omp_set_num_threads(5);
 #pragma omp parallel sections shared(num1, num2)
 {
	#pragma omp section
 	{
 		int sum = num1 + num2;
 		threadNum = omp_get_thread_num();
 		printf("\n Thread : %d \t Sum : %d", threadNum, sum);
 	}
 	#pragma omp section
 	{
 		int diff = num1 - num2;
 		threadNum = omp_get_thread_num();
 		printf("\n Thread : %d \t Difference : %d", threadNum, diff);
 	}
 	#pragma omp section
 	{
 		int prod = num1 * num2;
 		threadNum = omp_get_thread_num();
 		printf("\n Thread : %d \t Product : %d", threadNum, prod);
 	}
 	#pragma omp section
 	{
 		int div = num1 / num2;
 		threadNum = omp_get_thread_num();
 		printf("\n Thread : %d \t Division : %d", threadNum, div);
 	}
 	#pragma omp section
 	{
 		int rem = num1 % num2;
 		threadNum = omp_get_thread_num();
 		printf("\n Thread : %d \t Remainder : %d", threadNum, rem);
 	}
 }
 printf("\n");
}
