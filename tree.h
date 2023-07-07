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

extern Node* EXTERNAL;
Node* createEXTERNAL();

void remocao(Node**, Node*);
void insert_no(Node**, char*);

Node* criar_no(char*);

void imprime(Node* , int);

Node* busca(Node*, char*);

void lista_produtos(Node*, int);

#endif