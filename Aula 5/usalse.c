#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "listase.h"

static int* criar_num(int num){
    int* novo = malloc(sizeof(int));
    *novo = num;
    return novo;
}

void imprimir_num(void* num){
    int* novo_num = malloc(sizeof(num));
    
    printf("%d ", *novo_num);

}
struct msc
{
    char nome[100];
    int duracao;
};

struct msc* criar_musica(char *nome, int duracao){
    struct msc* nova = malloc(sizeof(struct msc));
    strcpy(nova->nome, nome);
    nova->duracao = duracao;
    
    return nova;
}

void imprimir_musica(void* m){
    struct msc* musica = (struct msc*) m;
    if (m == NULL)
        return;
    int min = musica->duracao/60;
    int seg = musica->duracao - min*60; 
    printf("%s (%d:%d)\n", musica->nome, min, seg);
}

int comparar_musica(void* m, void* nome_buscado){
    struct msc* musica = (struct msc*) m;
    char* nome = (char*) nome_buscado;
    return strcmp(musica->nome, nome_buscado);
}


int main(int argc, char const *argv[])
{
    int num;
    t_lse* deNumeros = criar_lse(imprimir_num, NULL, NULL);
    t_lse* deMusicas = criar_lse(imprimir_musica, comparar_musica, NULL);

    scanf("%d", &num);
    while(num!=-1){
        //inserir_lse(deNumeros, num);
        inserir_final_lse(deNumeros, criar_num(num));
        scanf("%d", &num);
    }

    // imprimir_lse(deNumeros);

    char nome[100];
    int duracao;
    scanf("%s", nome);
    while(strcmp(nome,"FIM")!=0){
        scanf("%d", &duracao);
        //inserir_lse(deNumeros, num);
        inserir_final_lse(deMusicas, criar_musica(nome, duracao));
        scanf("%s", nome);
    }

    imprimir_lse(deNumeros);
    imprimir_lse(deMusicas);
    
    scanf("%s", nome);
    struct msc *buscado = buscar_lse(deMusicas, nome);
    imprimir_musica(buscado);
    
    int *buscado_num = buscar_lse(deNumeros, &num);
    imprimir_num(buscado_num);
    return 0;
}
