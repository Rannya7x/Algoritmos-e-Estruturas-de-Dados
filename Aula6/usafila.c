//
#include "fila.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

typedef struct musica{
    char nome[60];
    char artista[30];
}t_musica;

t_musica* musica_criar(char* nome, char*artista){
    t_musica* nova = malloc(sizeof(t_musica));
    strcpy(nova->nome, nome);
    strcpy(nova->artista, artista);

    return nova;
}

void musica_imprimir(t_musica* musica){
    t_musica* m = musica;
    printf("%s", m->nome);
}

void* musica_reproduzir(t_musica* musica){
    t_musica* m = musica;
    printf("Reproduzindo %s - %s\n", m->nome, m->artista);
    return NULL;
}

void* musica_destruir(t_musica* musica){
    free(musica);
    return NULL;
}

int main(int argc, char const *argv[])
{
    char nome[60], artista[30];
    t_fila* preferidas = fila_criar();
    scanf("%s", nome);
    while(strcmp(nome,"FIM")!=0){
        scanf("%s", artista);
        fila_enfileirar(preferidas, musica_criar(nome, artista));
        scanf("%s", nome);
    }   
     
    t_musica* primeira = fila_cabeca(preferidas);
    musica_imprimir(primeira);
    musica_reproduzir(primeira);
    printf("tamanho: %d\n", fila_tamanho(preferidas));
    t_musica* removida = fila_desenfileirar(preferidas);
    musica_destruir(removida);

    return 0;
}
