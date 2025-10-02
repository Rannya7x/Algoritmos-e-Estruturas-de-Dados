#include "stdio.h"

typedef void(*t_func_ordenacao)(int* vetor, int tam);

int cmps;
int trocas;

static void trocar(int vetor[], int i, int j){
    trocas++;
    int aux =vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = aux;

}

void selecao(int vetor[], int N){
    for(int i=0;i< N-1; i++){
        int imenor = i; // Limite do NO
        for (int j=i+1;j<N;j++){
            cmps++;
            if (vetor[j] < vetor[imenor])
                imenor = j;
        }
        trocar(vetor, i, imenor);
    }
}

void insercao(int vetor[], int N){
    for(int i=1;i<N;i++){   
        int aux=vetor[i];
        int j=i-1; // i é a o limite do conjunto NO
        cmps++;
        while( (j>=0) && (vetor[j] > aux) ){    
            vetor[j+1]=vetor[j];
            j--;
            cmps++;
        }
        cmps = (j<0) ? cmps -1 : cmps; // Ajuste do excesso de comparação
        vetor[j+1] = aux;
    }
}

void bolha(int vetor[], int N){
    trocas=1;
    for (int i=0; (trocas != 0) && (i<N-1);i++){
        trocas=0;
        for(int j=N-1;j>i;j--){ // i limita o conjunto NO
            cmps++;
            if (vetor[j]>vetor[j-1]){
                trocar(vetor,j,j-1);
            }
        }
    }
}

void ordenar(t_func_ordenacao alg, int vetor[], int N){
    cmps=0;
    trocas=0;   
    alg(vetor, N);
    printf("Comparacoes: %d\n", cmps);
}

#define TAM 6
int main(int argc, char const *argv[])
{

    int vetor[TAM] = {1,3,4,6,10,12};
    ordenar(bolha, vetor, TAM);

    printf("\n---\n");
    for(int i=0;i<TAM;i++)
        printf("%d ", vetor[i]);
    printf("\n");
    printf("Trocas: %d\n", trocas);
    printf("Fim\n");
    return 0;
}
