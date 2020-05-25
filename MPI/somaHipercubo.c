#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>

#define TAM 16
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

	int vetor[TAM] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	int *p = vetor;
	int size, rank, tag=999, saida, entrada, dest, rem;

	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int valor = 0;
	int nivel = 2;//nivel maximo dos processadores. Só foi possivel até o nivel 2, visto que só temos 4 processadores
	int r = TAM/size;

	while(nivel>=1){
		dest = rank-nivel;
		rem = rank+nivel;
		if(rank>=nivel){
			saida=0;
			for(int i=0;i<r;i++){
				saida+=vetor[rank*r+i];
			}
			MPI_Send(&saida,1,MPI_INT,dest,tag,MPI_COMM_WORLD);
//			printf("Nivel %d P%d send %d to P%d\n",nivel,rank,saida,dest);
			nivel=0;
		}else{
			MPI_Recv(&entrada,1,MPI_INT,rem,tag,MPI_COMM_WORLD,&status);
			vetor[rank*r]+=entrada;
//			printf("nivel %d P%d received %d from %d and vetor[%d]=%d\n",nivel,rank,entrada,rem,rank*r,vetor[rank*r]);
//			print(vetor,"");
			nivel--;
		}
	}
	if(rank==0){
		for(int i=1;i<r;i++){
			vetor[0]+=vetor[i];
		}
		printf("Soma Final = %d\n",vetor[0]);
	}
	MPI_Finalize();
	return 0;
}
