/*
Using OpenMP, implement a Parallel Quick sort algorithm to sort a given set of elements and determine the time required to sort the elements. 
Repeat the experiment for different value of n, the number of elements in the list to be sorted. The elements can be read from a file or can be generated using the random number generator.
*/
#include<stdio.h>
#include<time.h>
#include<omp.h>
#define max 500

void qsort(int [],int,int);
int partition(int [],int,int);

void main(){
	int a[max],i,n;
	clock_t s,e;
	
	printf("Enter the value of n:");
	scanf("%d",&n);

	for(i=0;i<n;i++)
		a[i]=rand()%100;
	
	printf("\nThe Array Elements Before Sorting: \n");
	for(i=0;i<n;i++)
		printf("%d\t",a[i]);

	s=clock();
	qsort(a,0,n-1);
	e=clock();
	
	printf("\nElements of the Array After Sorting : \n");
	for(i=0;i<n;i++)
		printf("%d\t",a[i]);
	
	printf("\nTime Taken:%f",(e-s)/CLK_TCK);
	getch();
}
void qsort(int a[],int low,int high){
	int j;
	if(low<high){
		j=partition(a,low,high);
		qsort(a,low,j-1);
		qsort(a,j+1,high);
	}
}

int partition(int a[], int low,int high){
	int pivot,i,j,temp;
	pivot=a[low];
	i=low+1;
	j=high;
	while(1){
		while(pivot>a[i] && i<=high)
			i++;
		while(pivot<a[j])
			j--;
		if(i<j){
			temp=a[i];
			a[i]=a[j];
			a[j]=temp;
		}
		else{
			temp=a[j];
			a[j]=a[low];
			a[low]=temp;
			return j;
	}
	}
}
