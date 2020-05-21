#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>

#define TAM 12
//TAM deve ser multiplo de 3, visto que esta maquina só tem 4 processadores
// (1 mestre e 3 escravos)

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

	int vetor[TAM] = {8,7,5,6,4,3,2,1,0,20,-5,-20};
	int size, rank, destino, tag=999, r, atual[TAM], entrada[TAM], saida[TAM];

	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	r = TAM/(size-1);

	if(rank==0){
		for(int i=1;i<size;i++){
			//printf("PO send %d\n",r*i);	
			MPI_Send(vetor+r*(i-1), r, MPI_INT, 1, tag, MPI_COMM_WORLD);
			//printf("P%d send %d\n",rank,vetor[i]);
		}

		for(int i=1;i<size;i++){
			MPI_Recv(vetor+r*(i-1),r,MPI_INT,i,tag,MPI_COMM_WORLD,&status);
			//printf("P%d received final %d\n",rank,vetor[i-1]);
		}
		print(vetor,"");

	}else{
		MPI_Recv(atual,r,MPI_INT,rank-1,tag,MPI_COMM_WORLD,&status);
		//printSmall(atual,r);
		//printf("P%d received %d\n",rank,atual);
		for(int i = rank; i < size-1 ; i++){
			MPI_Recv(atual+r,r,MPI_INT,rank-1,tag,MPI_COMM_WORLD,&status);
			//printSmall(atual,2*r);
			insertionSortSequencial(atual,2*r);
			//printf("P%d recv %d\n",rank,entrada);
			//if(entrada < atual){
			///	saida = atual;
			//	atual = entrada;
			//}else{
			//	saida = entrada;
			//}
			//printf("P%d send %d\n",rank,saida);
			MPI_Send(atual+r,r,MPI_INT,rank+1,tag,MPI_COMM_WORLD);
		}
		MPI_Send(atual,r,MPI_INT,0,tag,MPI_COMM_WORLD);
		//printf("P%d send final %d\n",rank,atual);
		
	}
	MPI_Finalize();
	return 0;
}
