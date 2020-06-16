#include <stdlib.h>
#include <stdio.h>
#include "omp.h"

#define TAM 8

int main(){
	int A[TAM] = {1,2,3,4,10,12,8,5};
	int soma;
	int processor;
	omp_set_num_threads(4);
	#pragma omp parallel for
		for(int i=0;i<TAM;i++){
			//int numt = omp_get_num_threads();		
			int tid = omp_get_thread_num();
			printf("Processor %d add %d\n",tid,A[i]);
			soma+=A[i];		
		}

	printf("%d ",soma);	
	printf("\n");
}
