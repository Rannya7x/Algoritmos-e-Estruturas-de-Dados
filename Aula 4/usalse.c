#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "listase.h"

static int* criar_num(int num){
    int* novo = malloc(sizeof(int));
    *novo = num;
    return novo;
}

struct msc
{
    char nome[100];
    int duracao;
};

struct msc* criar_musica(char *nome, int duracao){
    struct msc* nova = malloc(sizeof(struct msc));

    return nova;
}


int main(int argc, char const *argv[])
{
    int num;
    t_lse* deNumeros = criar_lse();
    t_lse* deMusicas = criar_lse();

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
    return 0;
}
