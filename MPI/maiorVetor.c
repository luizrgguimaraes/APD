#include <stdio.h>
#include <mpi.h>

#define TAM 12

void mestreMaiorElemento(int size,int tag){
	MPI_Status status;
	int vetor[TAM] = {5,6,7,8,1,4,10,2,5,15,0,1};
	int maior = 0; 
	int maiorparcial;

	for(int dest=1;dest<size;dest++){
		
		int pos=dest*TAM/size;
		//printf("posicao = %d\n",pos);
		MPI_Send(vetor+pos, TAM/size, MPI_INT, dest, tag, MPI_COMM_WORLD);
	}
	for(int i=0;i<TAM/size;i++){
		if(vetor[i]>maior)maior = vetor[i];
	}
	printf("Processor %d/%d - maior = %d\n",0,size,maior);		
	for(int dest=0;dest<TAM/size;dest++){
		MPI_Recv(&maiorparcial,1,MPI_INT,MPI_ANY_SOURCE,tag,MPI_COMM_WORLD,&status);
		//printf("Processor Mestre - maiorParcial %d = %d\n",dest,maiorparcial);		
		if(maiorparcial>maior)maior = maiorparcial;
	}
	printf("Processor Mestre - maior = %d\n",maior);		


}
void escravoMaiorElemento(int rank,int size,int tag){
	MPI_Status status;
	int vetor[TAM];
	int source, maior=0;
	MPI_Recv(vetor,TAM/size,MPI_INT,0,tag,MPI_COMM_WORLD,&status);
	for(int i=0;i<TAM/size;i++){
		//printf("Processor %d received %d\n",rank,vetor[i]);
		if(vetor[i]>maior)maior = vetor[i];
	}
	printf("Processor %d/%d - maior = %d\n",rank,size,maior);		
	MPI_Send(&maior, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
	
}

int main(int argc, char **argv){
	int size;
	int rank;
	int length;
	char name[80];
	char newname[80];
	int dest = 0;
	int tag = 999;
		
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	//printf("Inicio da Execucao %d/%d\n",rank,size);
		
	if(rank==0){
		mestreMaiorElemento(size,tag);
	}else{
		escravoMaiorElemento(rank,size,tag);
	}
	//printf("Fim da Execucao %d/%d\n",rank,size);
	MPI_Finalize();
	return 0;
}	
