typedef struct fila t_fila;

t_fila* fila_criar();
void fila_enfileirar(t_fila* fila, void* elem);
void* fila_desenfileirar(t_fila* fila);
void* fila_cabeca(t_fila* fila);
int fila_tamanho(t_fila* fila);

