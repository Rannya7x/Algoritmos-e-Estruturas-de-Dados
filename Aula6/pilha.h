typedef struct pilha t_pilha;
t_pilha* pilha_criar();
void* pilha_desempilhar(t_pilha* pilha);
void pilha_empilhar(t_pilha* pilha, void* elem);
void* pilha_topo(t_pilha* pilha);
int pilha_altura(t_pilha* pilha);
