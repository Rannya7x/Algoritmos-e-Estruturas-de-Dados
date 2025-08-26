#include "stdio.h"
#include "stdlib.h"
#include "listase.h"

typedef struct elem_lse t_elemento_lse;
struct lse{
    t_elemento_lse* primeiro;
    t_elemento_lse* ultimo;
    int tamanho;
};

t_lse* criar_lse(){
    t_lse* nova = malloc(sizeof(t_lse));
    nova->primeiro = NULL;
    nova->ultimo = NULL;
    nova->tamanho = 0;

    return nova;
}

struct elem_lse
{
    int carga_util;
    t_elemento_lse* prox;
};

t_elemento_lse* criar_elem_lse(int carga){
    t_elemento_lse* novo = malloc(sizeof(t_elemento_lse));
    novo->carga_util = carga;
    novo->prox = NULL;

    return novo;
}

void inserir_lse(t_lse* lse, int carga){
    t_elemento_lse * novo = criar_elem_lse(carga);
    
    novo->prox = lse->primeiro;
    lse->primeiro = novo;
    lse->tamanho++;
    if(lse->ultimo == NULL){
        lse->ultimo = novo;
    }
}

void inserir_final_lse(t_lse* lse, int num){
    t_elemento_lse* novo = criar_elem_lse(num);
    if(lse->primeiro == NULL){ // lista vazia
        lse->primeiro = novo;
        lse->ultimo = novo;
    }else{
        lse->ultimo->prox = novo;
        lse->ultimo = novo;
    }
    lse->tamanho++;
}

int remover_lse(t_lse* lse){
    int num=-1;
    if (lse->ultimo == NULL){
        return num;
    }else if (lse->ultimo == lse->primeiro){
        t_elemento_lse* deletado = lse->primeiro;
        lse->primeiro = NULL;
        lse->ultimo = NULL;
        num = deletado->carga_util;
        free(deletado);
    }else{
        t_elemento_lse* deletado = lse->primeiro;
        lse->primeiro = lse->primeiro->prox;
        num = deletado->carga_util;
        free(deletado);
    }
    lse->tamanho--;
    return num;
}

void imprimir_lse(t_lse* lse){
    t_elemento_lse *cam = lse->primeiro;
    while(cam!=NULL){
        printf("%d ", cam->carga_util);
        cam = cam->prox;
    }
    printf("\n----\n");
}