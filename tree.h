#ifndef TREE_H
#define TREE_H

typedef enum cor{
    BLACK,
    RED
}Cor;

typedef struct node {
    char produto[300];
    Cor cor;
    int qtd_produto;
    struct node *esq;
    struct node *dir;
}Node;

typedef struct tree
{
    Node *raiz;
}Tree;

Tree* cria_tree();
Node* criar_no(char*);

#endif