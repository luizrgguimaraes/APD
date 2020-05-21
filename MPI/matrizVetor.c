/*
Multiplica uma matriz 4X4 por um vetor

MATRIZ
0 1 2 3
1 2 3 4
2 3 4 5
3 4 5 6
VETOR = 1 2 3 4
RESULTADO ESPERADO = 20 30 40 50


*/
#include <stdio.h>
#include <mpi.h>

#define TAM 8


void printMatriz(int matriz[TAM][TAM],int n,int m){
	
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			printf("%d ",matriz[i][j]);
		}
		printf("\n");
	}
}
void printVetor(int vetor[TAM],int n){
	for(int i=0;i<n;i++){
		printf("%d ",vetor[i]);
	}
	printf("\n");	
}
int main(int argc, char **argv){
	int size;
	int rank;
	char name[80];
	char newname[80];
	int dest = 0;
	int tag = 999;
	int matriz[TAM][TAM];
	for(int i=0;i<TAM;i++){
		for(int j=0;j<TAM;j++){
			matriz[i][j]=i+j;
		}
	}
	//printMatriz(matriz,TAM,TAM);
	int vetor[TAM] = {1,2,3,4,5,6,7,8};
	int x[TAM];
	int y[TAM];
	MPI_Init(&argc,&argv);
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int r=TAM/size;
	for(int i=0;i<TAM;i++){
		x[i]=0;
		for(int j=rank*r;j<r*(rank+1);j++){
			x[i]+=matriz[i][j]*vetor[j];			
			//printf("Processor %d/%d - matriz[%d][%d]=%d,vetor[%d]=%d,x[%d]=%d\n",rank,size,i,j,matriz[i][j],j,vetor[j],i,x[i]);
		}
	}
	//printVetor(x,TAM);
	if(rank>0){	
		MPI_Recv(y,TAM,MPI_INT,rank-1,tag,MPI_COMM_WORLD,&status);
		for(int i=0;i<TAM;i++){
			x[i]+=y[i];			
		}
	
		dest=rank+1;
		if(dest>=size)dest=0;
		MPI_Send(x, TAM, MPI_INT,dest, tag, MPI_COMM_WORLD);
	}else{
		MPI_Send(x, TAM, MPI_INT,rank+1, tag, MPI_COMM_WORLD);
		MPI_Recv(y,TAM,MPI_INT,MPI_ANY_SOURCE,tag,MPI_COMM_WORLD,&status);
		printVetor(y,TAM);
	}		
	MPI_Finalize();
	return 0;
}	

