#include <stdio.h>
#include <stdlib.h>
#include "ordena.h"

struct time {
    int ano, mes, dia, hora, minuto, segundo;
};

typedef struct info {
    int id_no;
    double temperatura;
    double luminosidade;
    double umidade;
    double velx_vento;
    struct time marca_tempo;
} t_info;

typedef struct {
    t_info** dataset;
    int tamanho;
}t_dataset;

t_dataset dataset_criar(char nome_arq[]){
    int lidos=0, tamanho=2;
    t_info** dataset = malloc(sizeof(t_info)*tamanho);
    FILE *fp = fopen(nome_arq, "r");
    if (!fp) {
        perror("Erro ao abrir arquivo");
        return (t_dataset){NULL,0};
    }

    // pular cabeçalho
    char header[256];
    fgets(header, sizeof(header), fp);
    printf("%s", header);
    struct info *dado =malloc(sizeof(t_info));

    
    while(fscanf(fp, "%d,%lf,%lf,%lf,%lf,%d-%d-%d %d:%d:%d",
                  &dado->id_no,
                  &dado->temperatura,
                  &dado->luminosidade,
                  &dado->umidade,
                  &dado->velx_vento,
                  &dado->marca_tempo.ano,
                  &dado->marca_tempo.mes,
                  &dado->marca_tempo.dia,
                  &dado->marca_tempo.hora,
                  &dado->marca_tempo.minuto,
                  &dado->marca_tempo.segundo) == 11){

                    dataset[lidos]=dado;
                    if (lidos == tamanho-1)
                        tamanho=tamanho*2;
                    lidos++;
                    dataset = realloc(dataset,tamanho*sizeof(t_info));
                    struct info *dado =malloc(sizeof(t_info));

    }
    free(dado);
    fclose(fp);

    return (t_dataset){dataset,lidos};

}

int main(int argc, char** argv) {
    printf("%s\n", argv[1]);
    t_dataset ds = dataset_criar(argv[1]);
    ordenar(bolha, ds.dataset, ds.tamanho);
    printf("%d\n", ds.tamanho);
    return 0;
}
