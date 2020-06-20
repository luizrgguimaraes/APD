#include <stdio.h>
#include <stdlib.h>


#define TAM 8


int solucoes=0;
void printMatriz(int m[TAM][TAM]){
	solucoes++;
	printf("Solucao %d\n",solucoes);
	for(int j=0;j<TAM;j++){
		for(int i=0;i<TAM;i++){
			if(m[i][j]==1){
				printf("%d ",i+1);
			}
		}
	}
	printf("\n");
	for(int i=0;i<TAM;i++){
		for(int j=0;j<TAM;j++){
			printf("%d ",m[i][j]);
		}
		printf("\n");
	}
	char c;
	scanf("%c",&c);
}


int rainha_salva(int tabuleiro[TAM][TAM],int linha,int coluna){
	int i,j;
	for(i=0;i<coluna;i++){//verifica a linha
		if(tabuleiro[linha][i] == 1)
			return 0;
	}
	for(i=linha, j=coluna;i>=0&&j>=0;i--,j--){//verifica a  diagonal noroeste
		if(tabuleiro[i][j] == 1)
			return 0;
	}
	for(i=linha, j=coluna;i<TAM && j > 0; i++, j--){//verifica a diagonal sudoeste
		if(tabuleiro[i][j] == 1)
			return 0;
	}


	return 1;

}

void posiciona_rainha(int tabuleiro[TAM][TAM], int coluna){
	if(coluna == TAM){
		printMatriz(tabuleiro);
		return;
	}
	for(int i=0;i<TAM;i++){
		if(rainha_salva(tabuleiro,i,coluna)){
			tabuleiro[i][coluna] = 1;
			posiciona_rainha(tabuleiro,coluna+1);
			tabuleiro[i][coluna] = 0;
		}

	}
}

int main(){
	
	int tabuleiro[TAM][TAM];
	for(int i=0;i<TAM;i++){
		for(int j=0;j<TAM;j++){
			tabuleiro[i][j] = 0;
		}
	}
	

	posiciona_rainha(tabuleiro,0);
	//printMatriz(tabuleiro);
	return 0;
}
