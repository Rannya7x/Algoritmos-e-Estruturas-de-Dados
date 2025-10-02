 for(i=1;i<N;i++){   
    aux=vetor[i];
    int j=i-1; // i é a o limite do conjunto NO
    while( (j>=0) && (vetor[j] > aux) ){    
        vetor[j+1]=vetor[j];
        j--;
    }
    vetor[j+1] = aux;
}