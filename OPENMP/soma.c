#include <stdlib.h>
#include <stdio.h>
#include "omp.h"

#define TAM 12

int main(){
	int A[TAM] = {1,2,40,11,12,13,21,22,23,31,32,33};
	int B[TAM] = {1,2,3,16,5,6,7,8,9,10,11,20}; 
	int soma[TAM];
	int processor;
	omp_set_num_threads(4);
	#pragma omp parallel for
		
		for(int i=0;i<TAM;i++){
			soma[i]=A[i]+B[i];
			//printf("Processor %d - i=%d - maior=%d\n",omp_get_thread_num(),i,soma[i]);	
		}
	for(int i=0;i<TAM;i++){
		printf("%d ",soma[i]);	
	}
	printf("\n");
}
