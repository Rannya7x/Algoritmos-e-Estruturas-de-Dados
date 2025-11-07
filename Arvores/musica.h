typedef struct musica t_musica;

t_musica* musica_criar(char *nome, int duracao);
void musica_imprimir(t_musica* m);
int musica_comparar(t_musica* m, char* nome_buscado);
