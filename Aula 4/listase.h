typedef struct lse t_lse;
t_lse* criar_lse();
void inserir_lse(t_lse* lse, void* carga);
void inserir_final_lse(t_lse* lse, void* carga);
void* remover_lse(t_lse* lse);
void* remover_final_lse(t_lse* lse);
void* acessar_lse(t_lse* lse, int pos);
void imprimir_lse(t_lse* lse);
