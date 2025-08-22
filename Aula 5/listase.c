#include "stdio.h"
#include "stdlib.h"
#include "listase.h"

typedef struct elem_lse t_elemento_lse;
struct lse{
    t_elemento_lse* primeiro;
    t_elemento_lse* ultimo;
    int tamanho;
    t_imprimir_lse impressora;
    t_comparar_lse comparar;
    t_inserir_conteudo_lse inserir_conteudo;
};

t_lse* criar_lse(t_imprimir_lse imp, t_comparar_lse comparar, t_inserir_conteudo_lse inserir_conteudo){
    t_lse* nova = malloc(sizeof(t_lse));
    nova->primeiro = NULL;
    nova->ultimo = NULL;
    nova->tamanho = 0;
    nova->impressora = imp;
    nova->comparar = comparar;
    nova->inserir_conteudo = inserir_conteudo;
    return nova;
}

struct elem_lse
{
    void* carga_util;
    t_elemento_lse* prox;
};

t_elemento_lse* criar_elem_lse(void* carga){
    t_elemento_lse* novo = malloc(sizeof(t_elemento_lse));
    novo->carga_util = carga;
    novo->prox = NULL;

    return novo;
}

void inserir_lse(t_lse* lse, void* carga){
    t_elemento_lse * novo = criar_elem_lse(carga);
    
    novo->prox = lse->primeiro;
    lse->primeiro = novo;
    lse->tamanho++;
    if(lse->ultimo == NULL){
        lse->ultimo = novo;
    }
}

void inserir_final_lse(t_lse* lse, void* carga){
    t_elemento_lse* novo = criar_elem_lse(carga);
    if(lse->primeiro == NULL){ // lista vazia
        lse->primeiro = novo;
        lse->ultimo = novo;
    }else{
        lse->ultimo->prox = novo;
        lse->ultimo = novo;
    }
    lse->tamanho++;
}

void* remover_lse(t_lse* lse){
    void* carga=NULL;
    if (lse->ultimo == NULL){
        return carga;
    }else if (lse->ultimo == lse->primeiro){
        t_elemento_lse* deletado = lse->primeiro;
        lse->primeiro = NULL;
        lse->ultimo = NULL;
        carga = deletado->carga_util;
        free(deletado);
    }else{
        t_elemento_lse* deletado = lse->primeiro;
        lse->primeiro = lse->primeiro->prox;
        carga = deletado->carga_util;
        free(deletado);
    }
    lse->tamanho--;
    return carga;
}

void imprimir_lse(t_lse* lse){
    t_elemento_lse *cam = lse->primeiro;
    while(cam!=NULL){
        //printf("%p ", cam->carga_util);
        lse->impressora(cam->carga_util);
        cam = cam->prox;
    }
    //printf("\n----\n");
}

void* buscar_lse(t_lse* lse, void* chave){
    t_elemento_lse* cam = lse->primeiro;
    while((cam!=NULL) && (lse->comparar(cam->carga_util, chave)!=0)){
        cam = cam->prox;
    }
    return (cam==NULL?NULL:cam->carga_util);
}

void inserir_conteudo_lse(t_lse* lse, void* conteudo){
    t_elemento_lse *novo = criar_elem_lse(conteudo);

    t_elemento_lse *anterior = NULL;
    t_elemento_lse *cam = lse->primeiro;
    while((cam!=NULL) &&  (lse->comparar(cam->carga_util, conteudo))<1){
        anterior = cam;
        cam = cam->prox;
    }
    if(anterior==NULL){
        novo->prox=lse->primeiro;
        lse->primeiro = novo;
        if(lse->ultimo==NULL){
            lse->ultimo = novo;
        }
    }else{
        novo->prox = cam;
        anterior->prox = novo;
        if(cam==NULL){
            lse->ultimo = novo;
        }
    }
    lse->tamanho++;
        
}

void* remover_conteudo_lse(t_lse* lse, void* conteudo){
    t_elemento_lse *anterior = NULL;
    t_elemento_lse *cam = lse->primeiro;

    while((cam!=NULL) && (lse->comparar(cam->carga_util, conteudo)!=0)){
        anterior = cam;
        cam = cam->prox;
    }
    if(cam==NULL){
        return NULL;
    }else{
        void *deletado = cam->carga_util;
        anterior->prox = cam->prox;
        free(cam);
        lse->tamanho--;
    }
    return deletado;
}