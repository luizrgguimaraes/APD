#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>

#define TAM 8
//TAM deve ser 4k, com K>=1, visto que esta maquina só tem 4 processadores

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


int main(int argc, char **argv){

	int matrizA[TAM][TAM];
	int matrizB[TAM][TAM];
	int matrizC[TAM][TAM];
	int count=0;
	for(int i=0;i<TAM;i++){
		for(int j=0;j<TAM;j++){
			matrizA[i][j]=count++;
		}
	}
	for(int i=0;i<TAM;i++){
		for(int j=0;j<TAM;j++){
			matrizB[i][j]=count++;
		}
	}

	int size, rank, tag=999;

	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int r = TAM*TAM/size;
	int rlinha = TAM/size;
	int soma;
	for(int linha=rank*rlinha;linha<(rank+1)*rlinha;linha++){
		for(int coluna=0;coluna<TAM;coluna++){
			soma=0;
			for(int i=0;i<TAM;i++){
				//printf("P%d calcula %d*%d \n",rank,matrizA[linha][i],matrizB[i][coluna]);	
				soma+=matrizA[linha][i]*matrizB[i][coluna];
			}
			if(rank>0){
				MPI_Send(&soma,1,MPI_INT,0,tag,MPI_COMM_WORLD);
				//printf("P%d send soma[%d][%d]=%d\n",rank,linha,coluna,soma);

			}else{
				matrizC[linha][coluna]=soma;
			}
				
		}
	}

	if(rank==0){
		printMatriz(matrizA,TAM);
		printMatriz(matrizB,TAM);
		for(int i=1;i<size;i++){
			for(int linha=i*rlinha;linha<(i+1)*rlinha;linha++){
				for(int coluna=0;coluna<TAM;coluna++){
					//printf("P%d received soma[%d][%d]\n",rank,linha,coluna);
					MPI_Recv(&matrizC[linha][coluna],1,MPI_INT,i,tag,MPI_COMM_WORLD,&status);
					
				}
			}			
		}
		printMatriz(matrizC,TAM);
	}
	MPI_Finalize();
	return 0;
}
