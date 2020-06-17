#include <stdlib.h>
#include <stdio.h>
#include "omp.h"

#define TAM 8

int max(int a, int b){
	if(a>b)return a;
	return b;
}

int main(){
	int A[TAM] = {1,2,3,4,10,12,8,5};
	int maior = 0;
	omp_set_num_threads(4);
	#pragma omp parallel default(shared) reduction(max:maior)
	{

		#pragma omp for 
		for(int i=0;i<TAM;i++){
			//int numt = omp_get_num_threads();		
			int tid = omp_get_thread_num();
			maior = max(maior,A[i]);
			printf("Processor %d maior %d\n",tid,A[i]);
		}
	}
	printf("%d ",maior);	
	printf("\n");
}
