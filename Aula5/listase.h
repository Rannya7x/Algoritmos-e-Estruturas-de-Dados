typedef void(*t_imprimir_lse)(void*);
typedef int(*t_comparar_lse)(void* arg_1, void* arg_2);
typedef void(*t_inserir_conteudo_lse)(void* arg_1, void* arg_2);
typedef void*(*t_remover_conteudo_lse)(void* arg_1, void* arg_2);

typedef struct lse t_lse;
t_lse* criar_lse(t_imprimir_lse impressora, t_comparar_lse comparar, t_inserir_conteudo_lse inserir_conteudo);
void inserir_lse(t_lse* lse, void* carga);
void inserir_final_lse(t_lse* lse, void* carga);
void* remover_lse(t_lse* lse);
void* remover_final_lse(t_lse* lse);
void* acessar_lse(t_lse* lse, int pos);
void imprimir_lse(t_lse* lse);
void* buscar_lse(t_lse* lse, void* buscado);
void inserir_conteudo_lse(t_lse* lse, void*conteudo);
void* remover_conteudo_lse(t_lse* lse, void* conteudo);
