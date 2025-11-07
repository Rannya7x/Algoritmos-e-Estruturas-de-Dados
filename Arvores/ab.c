#include "stdlib.h"
typedef struct no t_no;

struct no {
    t_no* actral;  
    t_no* sae;
    t_no* sad;
    void* info;
};
typedef void(*t_ab_imprimir)(void*);
typedef int(*t_ab_comparar)(void*, void*);
typedef struct ab {
    t_no* raiz;
    t_ab_imprimir imprimir;
    t_ab_comparar comparar;

} t_ab;

t_no* no_criar(void* info, t_no* actral){
    t_no* novo = malloc(sizeof(t_no));
    if(novo){
        novo->info = info;
        novo->sae = NULL;
        novo->sad = NULL;
        novo->actral = actral;
    }
    return novo;
}

t_ab* ab_criar(t_ab_imprimir imprimir, t_ab_comparar comparar){
    t_ab* nova = malloc (sizeof(t_ab));
    if(nova){
        nova->raiz = NULL;
        nova->imprimir = imprimir;
    }
    return nova;
}

static t_no* __ab_inserir(t_no* raiz, void* info, t_no* actral){
    if(raiz == NULL){// caso base: raiz é igual a nulo
        t_no* novo = no_criar(info, actral);
        return novo;
    }
    static int sorteio = 0;
    if(sorteio==0){ //insere arvore esquerda
        sorteio=1;
        raiz->sae = __inserir_ab(raiz->sae, info, raiz);
    }else{
        sorteio=0;
        raiz->sad = __inserir_ab(raiz->sad, info, raiz);
    }
    return raiz;
}
void ab_inserir(t_ab* ab, void* info){
    ab->raiz= __ab_inserir(ab->raiz, info, NULL);
}

static void __ab_caminhar_pre(t_no* raiz, t_ab_imprimir t_ab_imprimir){
    if (raiz == NULL){
        return;
    }
    imprimir(raiz->info);
    __ab_caminhar_pre(raiz->sae, t_ab_imprimir);
    __ab_caminhar_pre(raiz->sad, t_ab_imprimir);
}

void ab_caminhar(t_ab* ab){
    __ab_caminhar_pre(ab->raiz, ab->imprimir);

}
static void* __ab_buscar(t_no* raiz, t_ab_comparar comparar, void* chave){
    if (raiz == NULL){
        return NULL;
    }
    if(comparar(raiz->info, chave)==0){
        return raiz->info;
    }
    void* info = __ab_buscar(raiz->sae, comparar, chave);
    if (info == NULL){
        __ab_buscar(raiz->sad, comparar, chave);
    }
    return info;   
}
t_no* ab_buscar(t_ab* ab, void* chave){
    void* info = __ab_buscar(ab->raiz, ab->comparar, chave);
    return info;
}

t_no* ab_podar(t_ab* ab, void* chave){
    // implementação fictícia

}

void musica_imprimir(void* ms){
    printf("musica");
}
void musica_comparar(void* m1, void* m2){
    // implementação fictícia
}


int main(){
    t_ab* coleccao = ab_criar(musica_imprimir, musica_comparar);
    for(){
        ab_inserir(coleccao, nova_musica);
    }
    void* buscado = ab_buscar(coleccao, chave);
    return 0;
}