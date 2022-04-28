#include <stdio.h>
#include <stdlib.h>

typedef struct no No;

struct no{
    int valor;
    No *proximo;
};

typedef struct{
    int tamanho;
    No *head;
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

void inserirInicio(Lista *lista, int valor){
    No *novoNo = criarNo(valor);

    if(lista == NULL){
        lista->head = novoNo;
        lista->tamanho = lista->tamanho + 1;
    }

    if(lista != NULL){
        novoNo->proximo = lista->head;
        lista->head = novoNo;
        lista->tamanho = lista->tamanho + 1;
    }
}

void inserirFim(Lista *lista, int valor){
    No *novoNo = criarNo(valor);
    No *aux = lista->head;

    if(lista == NULL){
        lista->head = novoNo;
        lista->tamanho = lista->tamanho + 1;
    }

    if(lista != NULL){
        while(aux->proximo){
            aux = aux->proximo;
        }
        aux->proximo = novoNo;
        lista->tamanho = lista->tamanho + 1;
    }
}

void inserirApos(Lista *lista, int valor, int num){
    No *novoNo = criarNo(valor);
    No *aux = lista -> head;

    while(aux->valor != num && aux->proximo){
        aux = aux->proximo;
    }

    if(aux->valor == num){
        novoNo -> proximo = aux -> proximo;
        aux -> proximo = novoNo;
    }

    if(aux -> valor != num && aux->proximo == NULL){
        printf("Valor anterio não existe na lista\n");
    }
}

void removerInicio(Lista *lista){
    if(lista != NULL){
        No *aux = lista -> head;
        lista->head = aux->proximo;
        free(aux);
    }else{
        printf("Lista está vazia");
    }
}

void removerFim(Lista *lista){
    if(lista!= NULL){
        No *aux = lista -> head;
        while(aux->proximo->proximo){
            aux = aux->proximo;
        }
        No *ultimo = aux->proximo;
        aux->proximo = NULL;
        free(ultimo);
    }else{
        printf("Lista esta vazia");
    }
}

void remover(Lista *lista, int valor){
    if(lista!=NULL){
        No *aux = lista -> head; //aux = 1
        No *anterior;

        anterior->proximo == NULL;
        while(aux->valor != valor && aux->proximo){
            anterior = aux;
            aux = aux->proximo;
        }
        if(aux->valor == valor){
            //remove inicio
            if(anterior->proximo == NULL){
                lista->head = aux->proximo;
                free(aux);
            //remove do meio ou fim
            }else{
                anterior->proximo = aux->proximo;
                free(aux);
            }
        }else{
            printf("A lista nao contem o valor");
        }
    }
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

    inserirInicio(lista, 1);
    inserirApos(lista, 10, 1);
    inserirFim(lista, 5);


    printf("Insercoes:\n");
    listar(lista);
    printf("\n");

    //erro ao remover primeiro elemento
    remover(lista, 1);

    printf("Remocoes:\n");
    listar(lista);

    return 0;
}
