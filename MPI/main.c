#include <stdio.h>
#include <mpi.h>

#define TAM 12

void mestre(int size,int tag){
	MPI_Status status;
	int vetor[TAM] = {5,6,7,8,1,4,7,2,5,4,0,1};
	int soma = 0; 
	int somaparcial;

	for(int dest=1;dest<size;dest++){
		
		int pos=dest*TAM/size;
		//printf("posicao = %d\n",pos);
		MPI_Send(vetor+pos, TAM/size, MPI_INT, dest, tag, MPI_COMM_WORLD);
	}
	for(int i=0;i<TAM/size;i++){
		printf("Processor Mestre soma %d\n",vetor[i]);
		soma += vetor[i];
	}
	for(int dest=0;dest<TAM/size;dest++){
		MPI_Recv(&somaparcial,1,MPI_INT,MPI_ANY_SOURCE,tag,MPI_COMM_WORLD,&status);
		printf("Processor Mestre - somaParcial %d = %d\n",dest,somaparcial);		

		soma+= somaparcial;
	}
	printf("Processor Mestre - soma = %d\n",soma);		


}
void escravo(int rank,int size,int tag){
	MPI_Status status;
	int vetor[TAM];
	int source, soma=0;
	MPI_Recv(vetor,TAM/size,MPI_INT,0,tag,MPI_COMM_WORLD,&status);
	for(int i=0;i<TAM/size;i++){
		printf("Processor %d received %d\n",rank,vetor[i]);
		soma += vetor[i];
	}
	printf("Processor %d/%d - soma = %d\n",rank,size,soma);		
	MPI_Send(&soma, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
	
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
		mestre(size,tag);
	}else{
		escravo(rank,size,tag);
	}
	printf("Fim da Execucao %d/%d\n",rank,size);
	MPI_Finalize();
	return 0;
}	
int mainExemploMensagem(int argc, char **argv){
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
	
	if(rank>0){
		MPI_Get_processor_name(name,&length);
		snprintf(newname,80,"%s-%d",name,rank);
		MPI_Send(newname, 80, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
	}else{
		MPI_Status status;
		int source;
		for(source = 1; source < size; source++){
			MPI_Recv(name,80,MPI_CHAR,source,tag,MPI_COMM_WORLD,&status);
			printf("Menssage from %d/%d: %s\n",source, size,name);
		}
	}
	




	printf("Fim da Execucao %d/%d\n",rank,size);
	MPI_Finalize();
	return 0;
}
