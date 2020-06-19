#include <stdio.h>
#include <stdlib.h>


#define TAM 3

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



int main(){
	
	int s[TAM];
	int x[TAM];
	int v[TAM];
	for(int i=0;i<TAM;i++){
		s[i]=0;
		x[i]=0;
		v[i]=i+1;
	}

	permutacao(s,0,v,TAM,x);


	return 0;
}
