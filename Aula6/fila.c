#include "../Aula5/listase.h"
#include "fila.h"
#include "stdlib.h"

struct fila{
    t_lse* elems;
    int tamanho;
};

t_fila* fila_criar(){
    t_fila* nova = malloc(sizeof(t_fila));
    nova->elems = lse_criar(NULL,NULL);
    nova->tamanho = 0;
    
    return nova;
}

void fila_enfileirar(t_fila* fila, void* elem){
    if(fila == NULL)
        return;
    lse_inserir_final(fila->elems, elem);
    fila->tamanho++;
}

void* fila_desenfileirar(t_fila* fila){
    if (fila==NULL)
        return NULL;

    void *elem = lse_remover(fila->elems);
    if (elem)
        fila->tamanho--;
    return elem;
}

void* fila_cabeca(t_fila* fila){
    if (!fila)
        return NULL;
        
    void* elem = lse_acessar(fila->elems, 1);
    return elem;

}

int fila_tamanho(t_fila* fila){
    if(fila)
        return fila->tamanho;
    else    
        return -1;
}

void fila_destroy(t_fila* fila){
    // free(fila);
    return;
}