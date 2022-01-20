#include<stdio.h>
#include<omp.h>

void main()
{
  int i=0;
  int s=2;
  int e=50000;

  int j=0,count1=0,pc=0;

  #pragma omp parallel for reduction(+:pc)
  for(i=2; i<=e; i++) {
    int count1 = 0;
    for(j=1; j<=i; j++) {
       if((i%j) == 0) {
           count1++;
       }
    }
    if(count1 == 2) {
        pc++;
    }
}
  printf("%d\n",pc);
}
