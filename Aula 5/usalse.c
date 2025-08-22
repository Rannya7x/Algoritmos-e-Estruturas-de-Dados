#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "listase.h"

static int* criar_num(int num){
    int* novo = malloc(sizeof(int));
    *novo = num;
    return novo;
}

void imprimir_num(int* num){
    
    printf("%d ", *num);

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

void imprimir_musica(struct msc* m){
    if (m == NULL)
        return;
    int min = m->duracao/60;
    int seg = m->duracao - min*60; 
    printf("%s (%d:%d)\n", m->nome, min, seg);
}

int comparar_musica(struct msc* m, char* nome_buscado){
    return strcmp(m->nome, nome_buscado);
}


int main(int argc, char const *argv[])
{
    int num;
    t_lse* deNumeros = criar_lse(imprimir_num, NULL);
    t_lse* deMusicas = criar_lse(imprimir_musica, comparar_musica);

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
    
    int *buscado_num = busca_lse(deNumeros, num);
    imprimir_num(buscado_num);
    return 0;
}
