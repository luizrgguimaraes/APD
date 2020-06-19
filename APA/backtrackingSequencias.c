#include <stdio.h>
#include <stdlib.h>


#define TAM 3

void escreva(int *s){
	for(int i=0;i<TAM;i++){
		printf("%d ",s[i]);
	}
	printf("\n");
}

void mostraSequencias(int *s,int i, int *v, int n){
	if(i == n){
		escreva(s);
	}else{
		for(int j=0;j<n;j++){
			s[i] = v[j];
			mostraSequencias(s,i+1,v,n);
		}
	}
}



int main(){
	
	int s[TAM];
	int v[TAM];
	for(int i=0;i<TAM;i++){
		s[i]=0;
		v[i]=i+1;
	}
	
	mostraSequencias(s,0,v,TAM);


	return 0;
}
