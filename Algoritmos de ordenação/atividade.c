#include <stdio.h>
typedef void(*t_func_ordenacao)(int* vetor, int tam);
static trocar(int vetor[], int i, int j){
    int aux;
    aux=vetor[i];
    vetor[i]=vetor[j];
    vetor[j]=aux;
}

void insertion (int vetor[], int N){
    for(int i=1;i<N;i++){   
        int aux=vetor[i];
        int j=i-1; // i é a o limite do conjunto NO
        while( (j>=0) && (vetor[j] > aux) ){    
            vetor[j+1]=vetor[j];
            j--;
        }
        vetor[j+1] = aux;
    }
}
void bolha (int vetor[], int N){    
    for (int i=0;i<N-1;i++){
        for(int j=N-1;j>i;j--){ // i limita o conjunto NO
            if (vetor[j]>vetor[j-1]){
                trocar(vetor,j,j-1);
            }
        }       
    }
}

void selection(int vetor[], int N){ 
    for(int i=0;i< N-1; i++){
    int imenor = i; // Limite do NO
    for (int j=i+1;j<N;j++){
        if (vetor[j] < vetor[imenor])
            imenor = j;
    }
    trocar(vetor, i, imenor);
    }
}

ordenar(t_func_ordenacao alg, int vetor[], int N){
    alg(vetor,N);
}
#define TAM 10
int main (){
    int vetor[TAM] = {4,3,22,1};
    ordenar(selection, vetor, TAM);
    for (int i=0;i<5;i++)
        printf("%d ", vetor[i]);
    printf("\n");  
    return 0;
}
