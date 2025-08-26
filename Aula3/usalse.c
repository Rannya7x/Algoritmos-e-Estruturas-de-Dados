#include "stdio.h"
#include "listase.h"

int main()
{
    int num;
    t_lse* deNumeros = criar_lse();
    scanf("%d", &num);
    while(num!=-1){
        //inserir_lse(deNumeros, num);
        inserir_final_lse(deNumeros, num);
        scanf("%d", &num);
    }

    imprimir_lse(deNumeros);
    return 0;
}
