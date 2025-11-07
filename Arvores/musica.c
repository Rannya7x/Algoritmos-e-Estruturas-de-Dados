#include "stdio.h"
#include "stdlib.h"
#include "musica.h"

struct musica
{
    char nome[100];
    int duracao;
};

t_musica* musica_criar(char *nome, int duracao){
    t_musica* nova = malloc(sizeof(t_musica));
    strcpy(nova->nome, nome);
    nova->duracao = duracao;
    
    return nova;
}

void musica_imprimir(t_musica* m){
    if (m == NULL)
        return;
    int min = m->duracao/60;
    int seg = m->duracao - min*60; 
    printf("%s (%d:%d)\n", m->nome, min, seg);
}

int musica_comparar(t_musica* m, char* nome_buscado){
    return strcmp(m->nome, nome_buscado);
}
