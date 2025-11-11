#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//#include "../musica.h"

typedef struct Produto {
    int id;
    long preco; // em centavos (inteiro)
} Produto;

Produto* produto_criar(int id, long preco){
    Produto* novo_produto = malloc(sizeof(Produto));
    novo_produto->id = id;
    novo_produto->preco = preco;
    return novo_produto;
}

static int produto_comparar(void* p1, void* p2){
    Produto* prod1 = (Produto*) p1;
    Produto* prod2 = (Produto*) p2;
    if(prod1->preco > prod2->preco)|| (prod1->preco == prod2->preco && prod1->id > prod2->id) {
        return 1;
    } else if (prod1->preco < prod2->preco || (prod1->preco == prod2->preco && prod1->id < prod2->id)) {
        return -1;
    } else {
        return 0;
    }
}

Produto* kth(t_no* raiz, int k){
    // retorna o k-ésimo produto mais barato na árvore
    
}
percentile(t_no* raiz, double p){
    // retorna o produto no percentil p (0 < p < 100)
}

typedef struct no
{
    struct no *actral;
    struct no *sae;
    struct no *sad;
    void* info;
    int size;
}t_no;

static t_no* no_criar(void* info, t_no* actral){
    t_no* novo = malloc(sizeof(t_no));
    novo->info = info;
    novo->actral = actral;
    novo->sae = NULL;
    novo->sad = NULL;
    novo->size = 1;
    return novo;
}

typedef void (*t_abb_imprimir)(void*);
typedef int (*t_abb_comparar)(void*, void*);
typedef struct abb
{
    t_no* raiz;
    t_abb_imprimir imprimir;
    t_abb_comparar comparar;
}t_abb;

t_abb* abb_criar(t_abb_imprimir imprimir, t_abb_comparar comparar){
    t_abb *nova = malloc(sizeof(t_abb));
    nova->raiz = NULL;
    nova->imprimir = imprimir;
    nova->comparar = comparar;

    return nova;
}

static t_no* __abb_inserir(t_no* raiz, void* info, t_no* actral, t_abb_comparar comparar){
    if(raiz == NULL){
        t_no* novo = no_criar(info,actral);
        return novo;
    }else{
        int rest = comparar(raiz->info, info);
        if(rest > 0){ // inserir sae
            raiz->sae = __abb_inserir(raiz->sae, info, raiz, comparar);
        }else{ // inserir sad
            raiz->sad = __abb_inserir(raiz->sad, info, raiz, comparar);
        }
        return raiz;
    }
}

void abb_inserir(t_abb* abb, void* info){
    abb->raiz = __abb_inserir(abb->raiz, info, NULL, abb->comparar);
}


static t_no* __abb_buscar(t_no* raiz, t_abb_comparar comparar, void* chave){
    if (raiz == NULL){
        return NULL;
    }
    int res = comparar(raiz->info, chave); 
    if( res == 0){
        return raiz;
    } else if (res > 0){
        return __abb_buscar(raiz->sae, comparar, chave);
    } else {
        return __abb_buscar(raiz->sad, comparar, chave);
    }
}

void* abb_buscar(t_abb* abb, void* chave){
    
    t_no* no = __abb_buscar(abb->raiz, abb->comparar, chave);
    if (no!=NULL){
        return no->info;
    }
    return NULL;
}

static void __trocar(t_no* i1, t_no* i2){
    void* aux = i1->info;
    i1->info = i2->info;
    i2->info = aux;
}

static t_no* __abb_remover(t_no* raiz, t_abb_comparar comparar, void* chave, void* *placeholder){
    // caso base
    if (raiz == NULL){
        *placeholder=NULL;
        return NULL;
    }else{ // procura o nó a ser removido
        int res = comparar(raiz->info, chave);
        if(res > 0){ // se a comparação for maior, procura na sae
            raiz->sae = __abb_remover(raiz->sae, comparar, chave, placeholder);
            return raiz;
        } else if (res < 0){ // se a comparação for menor, procura na sad
            raiz->sad = __abb_remover(raiz->sad, comparar, chave, placeholder);
            return raiz;

        } else { // se comparação for igual, remove o nó
            if ( (raiz->sae == NULL) && (raiz->sad == NULL) ){ // subcaso 1: nó folha, sem filhos = sae e sad nulos
               *placeholder = (raiz->info);

               free(raiz);
               return NULL;     
            }else if ( (raiz->sae == NULL) && (raiz->sad != NULL) ){ // subcaso 2: nó com um filho, sad não nulo
                t_no* sad = raiz->sad;
                sad->actral = raiz->actral;
                
                *placeholder = (raiz->info);
                free(raiz);

                return sad;

            } else if ( (raiz->sae != NULL) && (raiz->sad == NULL) ){ // subcaso 3: nó com um filho, sae não nulo
                t_no* sae = raiz->sae;
                sae->actral = raiz->actral;

                *placeholder = (raiz->info);
                free(raiz);

                return sae;
            } else { // subcaso 4: nó com dois filhos
                t_no* no = raiz->sad;
                while (no->sae!=NULL){
                    no = no->sae;
                } 
                __trocar(raiz, no);
                raiz->sad = __abb_remover(raiz->sad,comparar,chave, placeholder);
                return raiz;
            }
        
        }

    }

}

void* abb_remover(t_abb* abb, void* chave){
    void* info=NULL;
    abb->raiz = __abb_remover(abb->raiz, abb->comparar, chave, &info);
    

    return info;
}


int main(int argc, char const *argv[])
{
    char nome[100]="INICIANDO";
    int duracao;
    char separador[4];
    
    t_abb* colecao = abb_criar(musica_imprimir, musica_comparar);
    
    char linha[1000];
    while (fgets(linha, sizeof(linha), stdin)) {
        sscanf(linha, "%[^;];%d", nome, &duracao);
        if (strcmp(nome, "FIM") == 0) break;
        t_musica* nova_msc = musica_criar(nome, duracao);
        abb_inserir(colecao, nova_msc);
    }


    printf("Iniciando a busca!\n");
    char buscado[100];
    while(fgets(linha, sizeof(linha), stdin)){
        sscanf(linha,"%[^;];", buscado);
        if (strcmp(buscado,"FIM")==0) break;
        t_musica* msc = abb_buscar(colecao, &buscado);
        if (msc != NULL){
            musica_imprimir(msc);
        }else{
            printf("%s não encontrado\n", buscado);
        }
    }
    printf("Iniciando remoção!\n");

    while(fgets(linha, sizeof(linha), stdin)){
        sscanf(linha,"%[^;];", buscado);
        if(strcmp(buscado,"FIM")==0) break;
        t_musica* msc = abb_remover(colecao, buscado);
        if (msc != NULL){
            musica_imprimir(msc);
            free(msc);
            printf("removido!\n");
        }else{
            printf("%s não encontrado", buscado);
        }
    }
    return 0;
}
