#include "stdio.h"
#include "stdlib.h"
#include "tree.h"
#include "string.h"

Tree *cria_tree(){
    Tree *raiz = malloc(sizeof(Tree));
    raiz->raiz = NULL;
    return raiz;
}

Node* criar_no(char* produto){
    Node* no = malloc(sizeof(Node));
    no->cor = RED;
    no->dir = no->esq = NULL;
    strcpy(no->produto, produto);
    no->qtd_produto = 0;
    return no;
}


