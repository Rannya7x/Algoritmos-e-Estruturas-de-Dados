#include "stdio.h"
#include "math.h"
#include "ordena.h"

static void __insercao(int elems[], int lim_i, int lim_j);

int total_cmps;
int total_trocas;

static void trocar(void* vetor[], int i, int j){
    total_trocas++;
    void* aux =vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = aux;

}

static int __particao(int vetor[], int lim_i, int lim_j){
    int i_pivo = (lim_i+lim_j)/2;
    int pivo = vetor[i_pivo];
    int i = lim_i;
    int j = lim_j-1;
    trocar(vetor, i_pivo, lim_j);
    do{
        while(vetor[i]<pivo){
            i++;
        }
        while( (j>=0) && (vetor[j]>pivo)){
            j--;
        }
        if (i < j){
            trocar(vetor,i,j);
            i++;j--;
        }
        //__mostrar(vetor, lim_i, lim_j);
        //printf("%d %d\n", i, j);
        //exit(0);
    }while(i < j);
    trocar(vetor,i,lim_j);
    return i;
}


static void __qs(int elems[], int lim_i, int lim_j){
    if((lim_j-lim_i)<=0){
        return;
    }else if ((lim_j-lim_i) <= 10) {
        __insercao(elems, lim_i, lim_j);
        return;
    }    
    int i_pivo = __particao(elems, lim_i, lim_j);
    __qs(elems, lim_i, i_pivo-1);
    __qs(elems, i_pivo+1, lim_j);
}

void qs(int elems[], int tam){
    __qs(elems, 0,tam-1);
    
}

static void __heap_subir(int elems[], int pos){
    int ancestral = (pos-1)/2;
    if ( (pos>0) && (elems[ancestral] < elems[pos])){
        trocar(elems, ancestral, pos);
        __heap_subir(elems,ancestral);
    }
}

static void __heap_descer(int elems[], int pos, int tamanho){
    int esq = 2*pos + 1;
    int dir = 2*pos + 2;
    int imenor = pos;
    if ((esq<tamanho) && (elems[pos] < elems[esq]) ){
        imenor = esq;
    }
    if ((dir<tamanho) && (elems[imenor] < elems[dir])){
        imenor = dir;
    }
    if(imenor != pos){
        trocar(elems, imenor, pos);
        __heap_descer(elems, imenor, tamanho);
    }
}

static void __heap_construir(int elems[], int tamanho){
    for (int i=1;i<tamanho;i++){
        __heap_subir(elems, i);
    }
}
static void __heap_construir_rl(int elems[], int tamanho){
    for (int i=(int)floor((tamanho-1)/2);i>0;i--){
        __heap_descer(elems,i, tamanho);
    }
}

void heap_sort(int elems[], int tamanho){
    __heap_construir_rl(elems, tamanho);
    for (int i=tamanho-1;i>0;i--){
        trocar(elems,0,i);
        __heap_descer(elems, 0, i-1);

    }
}

static void __intercalar(int elems[], int lim_i, int meio, int lim_j){
    int aux[lim_j-lim_i+1];
    int k = 0;
    int i=lim_i, j=meio+1;
    while((i<=meio) &&(j<=lim_j)){
        total_cmps++;
        if (elems[i]<=elems[j]){
            aux[k] = elems[i];
            i++;
        }else{
            aux[k] = elems[j];
            j++;
        }
        k++;
    }
    while(i<=meio){
        aux[k] = elems[i];
        i++;k++;
    }
    while(j<=lim_j){
        aux[k] = elems[j];
        j++;k++;
    }

    for(i=0;i<k;i++){
        total_trocas++;
        elems[lim_i+i] = aux[i];
    }
}

static void __ms(int elems[], int i, int j){
    if ((j-i)>=1){
        int meio = (i+j)/2;
        __ms(elems, i, meio);
        __ms(elems, meio+1, j);
        __intercalar(elems, i, meio, j);
    }
}

void merge_sort(int elems[], int tamanho){
    __ms(elems,0, tamanho-1);
}


void selecao(int vetor[], int N){
    for(int i=0;i< N-1; i++){
        int imenor = i; // Limite do NO
        for (int j=i+1;j<N;j++){
            total_cmps++;
            if (vetor[j] < vetor[imenor])
                imenor = j;
        }
        trocar(vetor, i, imenor);
    }
}

static void __insercao(int vetor[], int lim_i, int lim_f){
    for(int i=lim_i+1;i<=lim_f;i++){   
        int aux=vetor[i];
        int j=i-1; // i é a o limite do conjunto NO
        total_cmps++;
        while( (j>=0) && (vetor[j] > aux) ){    
            trocar(vetor, j,j+1);
            j--;
            total_cmps++;
        }
        total_cmps = (j<0?total_cmps-1:total_cmps);
        vetor[j+1] = aux;
    }
}

void insercao(int elems[], int N){
    __insercao(elems, 0, N-1);
}
void bolha(void* vetor[], int N, t_comparar_id cmp){
    int trocas=1;
    for (int i=0;((trocas!=0) && (i<N-1));i++){
        trocas=0;
        for(int j=N-1;j>i;j--){ // i limita o conjunto NO
            total_cmps++;
            if (cmp(vetor[j], vetor[j-1])<0){
                trocar(vetor,j,j-1);
                trocas = 1;
            }
        }
    }
}

void ordenar(t_func_ordenacao alg, void* vetor[], int N, t_comparar_id cmp){
    total_cmps = 0;
    total_trocas=0;
    alg(vetor, N, cmp);
    printf("comparacoes: %d\n", total_cmps);
    printf("Total de trocas: %d\n", total_trocas);
}
/*
#define TAM 6
int main(int argc, char const *argv[])
{
    int vetor[TAM] = {12,10,6,4,3,1};
    ordenar(qs, vetor, TAM);

    printf("\n---\n");
    for(int i=0;i<TAM;i++)
        printf("%d ", vetor[i]);
    printf("\n");
    return 0;
}
*/
