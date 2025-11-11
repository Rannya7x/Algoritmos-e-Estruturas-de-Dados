#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

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

int produto_comparar(void* p1, void* p2){
    Produto* prod1 = (Produto*) p1;
    Produto* prod2 = (Produto*) p2;
    if((prod1->preco > prod2->preco)|| (prod1->preco == prod2->preco && prod1->id > prod2->id) ){
        return 1;
    } else if (prod1->preco < prod2->preco || (prod1->preco == prod2->preco && prod1->id < prod2->id)) {
        return -1;
    } else {
        return 0;
    }
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
//retorna o size de um nó
static int size(t_no* no){
    if (no == NULL) return 0;
    return no->size;
}
static Produto* __kth(t_no* raiz, int k){
    if (raiz == NULL){
        return NULL;
    }
    //pega o tamanho da sae
    int sae_size = size(raiz->sae);

    //k-esimo elemento tá na sae
    if (k <= sae_size){
        return __kth(raiz->sae, k);
    //k-esimo é o da raiz
    }else if (k == sae_size + 1){ 
        return (Produto*) raiz->info;
    //k-esimo tá na sad
    }else{
        int novo_k = k - (sae_size + 1);
        return __kth(raiz->sad, novo_k);
    }
}

Produto* kth(t_abb* abb, int k){
    // retorna o k-ésimo produto mais barato na árvore
    int n = size(abb->raiz); //pega tamanho total da arvre
    if (k<=0 || k>n){
        return NULL; //k inválido
    }
    return __kth(abb->raiz, k);
}

Produto* percentile(t_abb* abb, double p){
    // retorna o produto no percentil p (0 < p < 100)
    int n = size(abb->raiz); //pega tamanho total da arvre
    if (n==0){
        return NULL; //árvore vazia
    }
    if (p <= 0|| p >= 1.0){
        return NULL; //percentil inválido
    }
    //converte p em k
    int k = (int) ceil(p * (double)n);
    return kth(abb, k);
}



static t_no* __abb_inserir(t_no* raiz, void* info, t_no* actral, t_abb_comparar comparar){
    if(raiz == NULL){
        t_no* novo = no_criar(info,actral);
        return novo;
    }else{
        int rest = comparar(raiz->info, info);
        //se comparação for igual, n insere
        if(rest == 0){ 
            return raiz;
        }
        if(rest > 0 ){ //preco na raiz é maior q o novo preço
            raiz->sae = __abb_inserir(raiz->sae, info, raiz, comparar); //precos menores vao pra esquerda

        }else {//preco na raiz é mnor
            raiz->sad = __abb_inserir(raiz->sad, info, raiz, comparar); //preco maior vai pra direita
        }

        // acumula novo valor do size
        raiz->size = 1 + size(raiz->sae) + size(raiz->sad);

        return raiz;// propaga a raiz atualizada
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

void produto_imprimir(Produto* p){
    if (p == NULL){
        return;
    }
    double preco_em_reais = ((double) p->preco)/100.0;
    printf("ID=%d PRECO=%.2f\n", p->id, preco_em_reais);
}

int main(int argc, char const *argv[])
{
    char comando[100];
    int id;
    double preco_lido;
    int k;
    double p;
    
    t_abb* produtos = abb_criar(NULL, produto_comparar);
    
    char linha[100];
    while (fgets(linha, sizeof(linha), stdin)) {
        if (sscanf(linha, "%s", comando) != 1){
            continue; //linha vazia ou erro
        }

        //insert
        if (strcmp(comando, "INSERT") == 0){
            if (sscanf(linha, "%*s %d %lf", &id, &preco_lido)==2){

                //preco em centavos
                long preco = (long) round(preco_lido * 100.0);
                //cria produto e insere na arvore
                Produto* novo = produto_criar(id, preco);
                abb_inserir(produtos, novo);
            }
        //kth
        }else if(strcmp(comando, "KTH") == 0){
            if (sscanf(linha, "%*s %d", &k) == 1){
                Produto* res = kth(produtos, k);
                if (res != NULL){
                    produto_imprimir(res);
                }
            }
        //percentile    
        }else if(strcmp(comando, "PERCENTILE") == 0){
            if (sscanf(linha, "%*s %lf", &p) == 1){
                Produto* res = percentile(produtos, p);
                if (res != NULL){
                    produto_imprimir(res);
                }
            }
        }
    }

    return 0;
}
