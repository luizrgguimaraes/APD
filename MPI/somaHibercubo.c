#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>

#define TAM 4
//numero de dimensoes

void printMatriz(int matriz[TAM][TAM],int N){
	for(int i=0;i<TAM;i++){
		for(int j=0;j<TAM;j++){
			printf("%d ",matriz[i][j]);
		}
		printf("\n");
	}
}


void print(int vetor[],char *rotulo){
	printf("%s ",rotulo);
	for(int i=0;i<TAM;i++){
		printf("%d ",vetor[i]);
	}
	printf("\n");
}

void printSmall(int *vetor, int N){
	for(int i=0;i<N;i++){
		printf("%d ",vetor[i]);
	}
	printf("\n");
}


void insertionSortSequencial(int vetor[], int N){
	int i,j,key;


	for(i=1;i<N;i++){
		key = vetor[i];
		//printf("vetor[%d]=%d\n",i,vetor[i]);
		j=i-1;
		while(j>=0 && vetor[j] > key){
			vetor[j+1] = vetor[j];
			
			//printf("(%d,%d) ",j,i);
			//print(vetor,"");

			j--;
		}
		vetor[j+1]=key;	
		//print(vetor,"=");
	}
}
int potencia(int b, int e){
	int p = b;
	for(int i=1;i<e;i++){
		p *= b;
	}
	return p;
}

int main(int argc, char **argv){

	int vetor[TAM*TAM] = {5,6,7,8};

	int size, rank, tag=999, saida[2], entrada, dest, rem;

	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	//int r = TAM*TAM/size;
	int valor = vetor[rank];
	int nivel = size/2;//size/log TAM na base 2

	
	while(nivel>=1){
		dest = rank-nivel;
		rem = rank+nivel;
		if(rank>=nivel){
			MPI_Send(&valor,1,MPI_INT,dest,tag,MPI_COMM_WORLD);
			//printf("nivel %d P%d send %d to %d\n",nivel,rank,valor,dest);
			nivel=0;
		}else{
			//printf("nivel %d P%d received from %d\n",nivel,rank,rem);
			MPI_Recv(&entrada,1,MPI_INT,rem,tag,MPI_COMM_WORLD,&status);
			valor+=entrada;
			nivel--;
		}
	}
	//for(int i=rank;rank>0&&i<)

				//printf("P%d send soma[%d][%d]=%d\n",rank,linha,coluna,soma);
	if(rank==0){
		printf("Soma Final = %d\n",valor);
	}
	MPI_Finalize();
	return 0;
}
