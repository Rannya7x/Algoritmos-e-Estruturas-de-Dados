bolha () {
    for (i=0;i<N-1;i++){
        for(j=N-1;j>i;j--){ // i limita o conjunto NO
            if (vetor[j]>vetor[j-1]){
                trocar(vetor,j,j-1);
            }
        }       
    }
}