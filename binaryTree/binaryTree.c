#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;


struct node{
    int data;
    Node *left;
    Node *right;
};

Node* createNode(int data){
    Node *newNode = (Node*)malloc(sizeof(Node));
    if(newNode){
        newNode->data = data;
        newNode->left =  NULL;
        newNode->right = NULL;
    }else{
        printf("Erro ao alocar memória");
    }
    return newNode;
}

Node* createTree(){
    return NULL;
};

Node* inserir(Node *tree, int data){
    Node *newNode = createNode(data);

    if(tree == NULL )return newNode;

    if(newNode->data < tree->data){
        tree->left = inserir(tree->left, newNode->data);
    }else{
        tree->right = inserir(tree->right, newNode->data);
    }
    return tree;
}

Node* buscar(Node *tree, int data){

    if(tree == NULL) return NULL;

    if(data == tree->data) return tree;

    if(tree->data > data){
        return buscar(tree->left, data);
    }

    return buscar(tree->right, data);

}

int contadorNos(Node *tree){

    if(tree == NULL) return 0;

    return contadorNos(tree->left) + 1 + contadorNos(tree->right);

}

void listar(Node *tree){
    if(tree != NULL){
        printf("%d", tree->data);
        printf("(");
        listar(tree->left);
        listar(tree->right);
        printf(")");
    }
}

int main(){
    Node *binaryTree;
    Node *data;
    binaryTree = createTree();

    binaryTree = inserir(binaryTree, 5);
    binaryTree = inserir(binaryTree, 10);
    binaryTree = inserir(binaryTree, 4);

    printf("Listagem da arvore:\n\n");
    listar(binaryTree);
    printf("\n");

    printf("\n quantidade de nos = %d\n", contadorNos(binaryTree));

    data = buscar(binaryTree, 10);
    printf("\nbuscar = %p\n", data);

    return 0;
};
