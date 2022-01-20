/*
Write an OpenMP program to find and sum the Fibonacci series. Use one thread to generate the  numbers  up  to  the  specified  limit  N=50000  and  other  threads  has  to  sum  and  print them. Use omp reduction to protect the code region that might be updated by multiple threads concurrently. Measure the execution time for both versions (omp critical) varying the number of threads: 4 and 8.
*/
#include<stdio.h>
#include<omp.h>

int main() {

   int n,i;
   omp_set_num_threads(4);
   printf("Enter the Number of Terms of Fibonacci Series which have to be generated : \n");
   scanf("%d",&n);
   int a[n];
   a[0]=0;
   a[1]=1;
   #pragma omp parallel
   {
    	  #pragma omp single
    	  for(i=2;i<n;i++)
    	  {
           	a[i]=a[i-2] + a[i-1];
     		printf("Id of Thread Involved in the Computation of Fibonacci Number %d is = %d \n", i+1, omp_get_thread_num());
   	  }
          #pragma omp barrier
          #pragma omp single
    	 {
       		printf("The Elements of Fibonacci Series Are : \n");
       		for(i=0;i<n;i++)
       			printf("%d,Id of Thread Displaying This Number Is =  %d \n", a[i], omp_get_thread_num());
   	 }
   }
   return 0;
}
