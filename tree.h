#ifndef TREE_H
#define TREE_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef enum cor
{
    BLACK,
    RED
}Cor;

typedef enum bool{
    False,
    True
}Bool;

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

extern Node* EXTERNAL;
Node* createEXTERNAL();

void remocao(Node**, Node*);

Node* insertRoot(Node*, char*, int);

Node* insert(Node*, char*, int);

Node* criar_no(char*, int);

void imprime(Node* , int);

Node* busca(Node*, char*);

void printEstoque(Node*);

void printTreeHelper(Node*);

#endif