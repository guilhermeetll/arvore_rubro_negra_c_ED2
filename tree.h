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

typedef struct FPTA {
    Node* filho; //Armazena filho que no caso é o valor que procuramos
    Node* pai;   //Armazena Pai
    Node* tio;   //Armazena Tio
    Node* avo;   //Armazena Avo
}FPTA;


Node* criar_no(char*, int);

void imprime(Node*, int);

Node* busca(Node*, char*);

Node* insert(Node*, char*);

Node* insertRoot(Node*, char*);

FPTA* returnFamilia(Node*, char*);

#endif