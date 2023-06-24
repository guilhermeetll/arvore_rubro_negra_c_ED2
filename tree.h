#ifndef TREE_H
#define TREE_H

typedef enum cor
{
    BLACK,
    RED
}Cor;

typedef struct node 
{
    char produto[300];
    Cor cor;
    int qtd_produto;
    struct node *esq;
    struct node *dir;
}Node;


Node* criar_no(char*);

void imprime(Node* , int);

Node* busca(Node*, char*);

#endif