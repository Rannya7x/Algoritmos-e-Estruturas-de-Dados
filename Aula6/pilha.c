#include "../Aula5/listase.h"
#include "stdlib.h"
#include "pilha.h"

struct pilha{
    t_lse* elems;
    int altura;
};

t_pilha* pilha_criar(){
    t_pilha* nova = malloc(sizeof(t_pilha));
    
    nova->elems = lse_criar(NULL, NULL);
    nova->altura=0;

    return nova;
}

void* pilha_desempilhar(t_pilha* pilha){
    if(!pilha)
        return NULL;
    
    void* elem = lse_remover(pilha->elems);
    if(elem)
        pilha->altura--;
    return elem;
}

void pilha_empilhar(t_pilha* pilha, void* elem){
    if(!pilha)
        return
    
    lse_inserir(pilha->elems,elem);
    pilha->altura++;
}

void* pilha_topo(t_pilha* pilha){
    if(!pilha)
        return NULL;
    
    void* elem = lse_acessar(pilha->elems, 1);
    return elem;
}

int pilha_altura(t_pilha* pilha){
    if(!pilha)
        return -1;
    
    return pilha->altura;
}

void pilha_destroy(){

}