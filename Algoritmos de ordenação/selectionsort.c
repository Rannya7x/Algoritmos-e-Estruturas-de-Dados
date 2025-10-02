for(i=0;i< N-1; i++){
    imenor = i; // Limite do NO
    for (j=i+1;j<N;j++){
        if (vetor[j] < vetor[imenor])
            imenor = j;
    }
    trocar(vetor, i, imenor);
}