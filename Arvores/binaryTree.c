#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;

struct node{
    int data;
    Node *left;
    Node *right;
};

typedef struct{
    int tamanho;
    Node *root;
}BinaryTree;

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

BinaryTree* createTree(){
    BinaryTree *newTree = (BinaryTree*)malloc(sizeof(BinaryTree));
    if(newTree){
        newTree->root = NULL;
    }else{
        printf("Erro ao alocar memória");
    }
    return newTree;
};

void inserirNo(Node *node, int data){
    if(node != NULL){
        if(data < node->data){
            inserirNo(node->left, data);
        }else{
            inserirNo(node->right, data);
        }
    }else{
        node = createNode(data);
    }
}

void inserir(BinaryTree *tree, int data){
    if(tree->root == NULL){
        tree->root = createNode(data);
    }else{
        inserirNo(tree->root, data);
    }

}

Node* buscarEnderecoNo(Node *tree, int data){

    if(tree == NULL) return NULL;

    if(data == tree->data) return tree;

    if(tree->data > data){
        return buscarEnderecoNo(tree->left, data);
    }

    return buscarEnderecoNo(tree->right, data);

}

int contadorNos(BinaryTree *tree){

    return tree->tamanho;

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
    BinaryTree *binaryTree = createTree();

    //for(int i=0; i<6;i++){
    //    inserir(binaryTree, i);
    //}

    inserir(binaryTree, 5);
    inserir(binaryTree, 4);

    printf("Listagem da arvore:\n\n");
    listar(binaryTree->root);
    printf("\n");

    return 0;
};
