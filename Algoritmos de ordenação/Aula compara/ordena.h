typedef int(*t_comparar_id)(void* arg_1, void* arg_2);
typedef void(*t_func_ordenacao)(void* vetor[], int tam, t_comparar_id cmp);
void qs(int elems[], int tam);
void heap_sort(int elems[], int tamanho);
void merge_sort(int elems[], int tamanho);
void selecao(int vetor[], int N);
void insercao(int elems[], int N);
void bolha(void* vetor[], int N, t_comparar_id cmp);
void ordenar(t_func_ordenacao alg, void* vetor[], int N, t_comparar_id cmp);