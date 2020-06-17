#include <stdlib.h>
#include <stdio.h>
#include "omp.h"

#define TAM 12

int max(int a,int b){
	if(a>b)return a;
	return b;
}
int main(){
	int A[TAM] = {1,2,40,11,12,13,21,15,23,8,7,50};
	int maior = 0;
	omp_set_num_threads(4);
	#pragma omp parallel
	{
		int processor = omp_get_thread_num();
		int nprocessors = omp_get_num_threads();		
		int r = TAM/nprocessors;
		for(int i=0;i<r;i++){
			maior = max(maior,A[processor*r+i]);	
			//printf("Processor %d - i=%d - maior=%d\n",processor,i,maior);	
		}
	}
	printf("Maior: %d\n",maior);	
}
