#include <stdio.h>
#include <stdlib.h>


#define TAM 4

void escreva(int *s){
	for(int i=0;i<TAM;i++){
		printf("%d ",s[i]);
	}
	printf("\n");
}

void permutacao(int *s,int i, int *v, int n,int *x){
	if(i == TAM	){
		escreva(s);
	}else{
		for(int j=0;j<n;j++){
			if(x[j]==0){
				x[j]=1;
				s[i]=v[j];
				permutacao(s,i+1,v,n,x);
				x[j]=0;

			}

		}
	}
}

int solucoes=0;
void printMatriz(int m[TAM][TAM]){
	solucoes++;
	printf("Solucao %d\n",solucoes);
	for(int i=0;i<TAM;i++){
		for(int j=0;j<TAM;j++){
			printf("%d ",m[i][j]);
		}
		printf("\n");
	}
}


int valor_valido(int valor,int m[TAM][TAM],int linha,int coluna){
	for(int i=0;i<TAM;i++){
		if(m[linha][i] == valor || m[i][coluna]==valor){
			return 0;
		}

	}
	return 1;

}

void sudoku(int m[TAM][TAM],int linha, int coluna){
	if(coluna == 4){
		linha++;
		coluna=0;
	}
	if(linha==4){
		printMatriz(m);
		return;
	}
	if(m[linha][coluna]>0){
		sudoku(m,linha,coluna+1);
		return;
	}
	for(int i=1;i<=4;i++){
		if(valor_valido(i,m,linha,coluna)){
			//printf("valor valido\n");
			m[linha][coluna] = i;
			sudoku(m,linha,coluna+1);
			m[linha][coluna] = 0;
		}

	}
}

int main(){
	
	int m[TAM][TAM];
	m[0][0]=0;	m[0][1]=2;	m[0][2]=4;	m[0][3]=0;
	m[1][0]=1;	m[1][1]=0;	m[1][2]=0;	m[1][3]=3;
	m[2][0]=4;	m[2][1]=0;	m[2][2]=0;	m[2][3]=2;
	m[3][0]=0;	m[3][1]=1;	m[3][2]=3;	m[3][3]=0;

	sudoku(m,0,0);
	return 0;
}
