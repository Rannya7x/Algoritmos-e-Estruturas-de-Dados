#include <stdio.h>
#include <stdlib.h>

typedef struct no No;

struct no{
    int valor;
    No *proximo;
};

No* criarLista(){
    return NULL;
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

int tamanho(No *lista){
    No *aux = lista;
    int tam = 0;
    while(aux){
        aux = aux->proximo;
        tam++;
    }
    return tam;
}

No* inserirInicio(No *head, int valor){
    No *novoNo = criarNo(valor);
    if(head != NULL){
        novoNo -> proximo = head;
    }
    return novoNo;
}

No* inserirFim(No *head, int valor){
    No *novoNo = criarNo(valor);
    No *aux = head;

    if(head != NULL){
        while(aux->proximo){
            aux = aux->proximo;
        }
        aux->proximo = novoNo;
    }else{
        return novoNo;
    }
    return head;
}

No* inserirMeio(No *head, int valor, int anterior){
    No *novoNo = criarNo(valor);
    No *aux = head;

    while(aux->valor != anterior && aux->proximo){
        aux = aux->proximo;
    }
    novoNo->proximo = aux->proximo;
    aux->proximo = novoNo;
    return head;
}

No* removerInicio(No *head){
    if(head!=NULL){
        No *aux = head;
        head = aux->proximo;
        free(aux);
    }
    return head;
}

No* removerFim(No *head){
    if(head!=NULL){
        No *aux = head;
        while(aux->proximo->proximo){
            aux = aux->proximo;
        }
        No *ultimo = aux->proximo;
        aux->proximo = NULL;
        free(ultimo);
    }
    return head;
}

No* remover(No *head, int valor){
    if(head!=NULL){
        No *aux = head;
        No *anterior;
        while(aux->valor != valor && aux->proximo){
            anterior = aux;
            aux = aux->proximo;
        }
        if(aux == head){
            return removerInicio(head);
        }
        if(aux->proximo==NULL){
            removerFim(head);
        }

        anterior->proximo = aux->proximo;
        free(aux);
    }
    return head;
}

void listar(No *lista){
    No *aux = lista;
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
    No *lista;
    No *chave;
    lista = criarLista();
    for(int i = 0; i<6;i++){
        lista = inserirFim(lista, i);
    }
    listar(lista);
    lista = removerFim(lista);
    printf("\nRemovido\n");
    listar(lista);

    return 0;
}
