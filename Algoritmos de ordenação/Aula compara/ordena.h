#include "ordena.c"

typedef void(*t_func_ordenacao)(int* vetor, int tam);
void qs(int elems[], int tam);
void heap_sort(int elems[], int tamanho);
void merge_sort(int elems[], int tamanho);
void selecao(int vetor[], int N);
void insercao(int elems[], int N);
void bolha(int vetor[], int N);
void ordenar(t_func_ordenacao alg, int vetor[], int N);