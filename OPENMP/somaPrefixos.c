#include <stdlib.h>
#include <stdio.h>
#include "omp.h"

#define TAM 8

void printVetor(int *vetor,int inicio,int N){
	
	for(int i=inicio; i<N; i++){
		printf("%d ",vetor[i]);
	}
	printf("\n");
}

int logaritmo(int logaritmando){
	int i  = 0;
	do{
		logaritmando/=2;
		i++;	
	}while(logaritmando >1);
	return i;
}

int potencia(int expoente){
	int res = 1;
	for(int i = 0;i<expoente;i++){
		res*=2;
	}
	return res;
}

int main(){
	int A[TAM] = {2,3,1,3,1,4,2,1};
	int P[TAM*2];
	for(int i=0;i<(TAM*2);i++)
		P[i]=0;
	int B[TAM*2];
	for(int i=0;i<(TAM*2);i++)
		B[i]=0;
	int maior = 0;
	int acumulo;
	omp_set_num_threads(4);
	#pragma omp parallel for
		for(int i=0;i<TAM;i++)
			B[TAM+i] = A[i];

	for(int j =logaritmo(TAM)-1;j>=0;j--){//logaritmo(TAM)
		//printf("loop j = %d\n",j);
		//printf("potencia j = %d/ potencia j+1 = %d\n",potencia(j),potencia(j+1)-1);
		#pragma omp parallel for
			for(int i=potencia(j);i<=(potencia(j+1)-1);i++){
				//int processor = omp_get_thread_num();
				//printf("processor %d calc B[%d] = B[%d]+B[%d]\n",processor,i,2*i,2*i+1);
				B[i] = B[2*i]+B[2*i+1];
			}
	}
	//printVetor(B,0,TAM*2);	


	P[1] = B[1];
	for(int j = 1; j<=logaritmo(TAM);j++){
		#pragma omp parallel for
			for(int i=potencia(j);i<=(potencia(j+1)-1);i++){
				if(i%2==0)
					P[i] = P[i/2]-B[i+1];
				else
					P[i] = P[(i-1)/2];
			}
		
	}

	printVetor(P,TAM,TAM*2);	


}
