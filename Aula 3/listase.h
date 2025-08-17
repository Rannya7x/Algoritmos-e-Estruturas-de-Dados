typedef struct lse t_lse;
t_lse* criar_lse();
void inserir_lse(t_lse* lse, int carga);
void inserir_final_lse(t_lse* lse, int carga);
int remover_lse(t_lse* lse);
int remover_final_lse(t_lse* lse);
int acessar_lse(t_lse* lse, int pos);
void imprimir_lse(t_lse* lse);
