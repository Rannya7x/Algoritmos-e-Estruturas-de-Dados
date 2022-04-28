#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int valor;
    struct No *proximo;
}No;

typedef struct{
    int tamanho;
    struct No *head;
}Lista;

Lista* criarLista(){
    Lista *lista = (Lista*)malloc(sizeof(Lista));
    if(lista){
        lista -> tamanho = 0;
        lista -> head = NULL;
    }else{
        printf("Erro ao alocar memoria");
    }

    return lista;
}

No* criarNo(int valor){
    No *novoNo = (No*)malloc(sizeof(No));
    if(novoNo){
        novoNo->valor = valor;
        novoNo->proximo = NULL;
    }
    else{
        printf("Erro ao alocar memoria\n");
    }
    return novoNo;
}

No* inserirInicio(Lista *lista, int valor){
    No *novoNo = criarNo(valor);

    if(lista->head == NULL){
        lista->tamanho = lista->tamanho + 1;
        return novoNo;
    }

    novoNo->proximo = lista->head;
    lista->head = novoNo;
    lista->tamanho = lista->tamanho + 1;

    return novoNo;
}

No* inserirFim(Lista *lista, int valor){
    No *novoNo = criarNo(valor);
    No *aux = lista->head;

    if(lista-> head == NULL){
        lista->tamanho = lista->tamanho + 1;
        return novoNo;
    }

    if(lista->head != NULL){
        while(aux->proximo){
            aux = aux->proximo;
        }
        aux->proximo = novoNo;
    }

    lista->tamanho = lista -> tamanho + 1;

    return lista->head;
}

No* inserirApos(Lista *lista, int valor, int num){
    No *novoNo = criarNo(valor);
    No *aux = lista -> head;

    while(aux->valor != num && aux->proximo){
        aux = aux->proximo;
    }

    if(aux -> valor != num && aux->proximo == NULL) return lista->head;

    novoNo -> proximo = aux -> proximo;
    aux -> proximo = novoNo;

    return lista->head;
}

No* removerInicio(Lista *lista){
    if(lista -> head != NULL){
        No *aux = lista -> head;
        lista -> head = aux->proximo;
        free(aux);
    }
    return lista -> head;
}

No* removerFim(Lista *lista){
    if(lista -> head != NULL){
        No *aux = lista -> head;
        while(aux->proximo->proximo){
            aux = aux->proximo;
        }
        No *ultimo = aux->proximo;
        aux->proximo = NULL;
        free(ultimo);
    }
    return lista -> head;
}

No* remover(Lista *lista, int valor){
    if(lista -> head!=NULL){
        No *aux = lista -> head;
        No *anterior;
        while(aux->valor != valor && aux->proximo){
            anterior = aux;
            aux = aux->proximo;
        }
        if(aux == lista -> head){
            return removerInicio(lista -> head);
        }
        if(aux->proximo==NULL){
            removerFim(lista -> head);
        }

        anterior->proximo = aux->proximo;
        free(aux);
    }
    return lista -> head;
}

void listar(Lista *lista){
    No *aux = lista -> head;
    while(aux){
        printf("%d\n", aux->valor);
        aux = aux->proximo;
    }
}

No* buscar(No *head, int valor){
    No *aux = head;
    while(aux){
        if(aux->valor == valor){
            return aux;
        }
        aux = aux->proximo;
    }
    return NULL;
}

int main(){
    Lista *lista = criarLista();
    for(int i = 0; i<6;i++){
       lista -> head = inserirFim(lista, i);
    }
    listar(lista);

    return 0;
}
