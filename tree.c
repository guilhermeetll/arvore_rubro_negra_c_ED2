#include "stdio.h"
#include "stdlib.h"
#include "tree.h"
#include "string.h"


Node* criar_no(char* produto){
    Node* no = malloc(sizeof(Node));
    no->cor = BLACK;
    no->esq = NULL;
    no->dir = NULL;
    strcpy(no->produto, produto);
    no->qtd_produto = 0;
    return no;
}

void imprime(Node* raiz, int b){
    if (raiz){
        imprime(raiz->dir, b+1);
        for (int i = 0; i < b; i++) printf("      ");
        printf("%s\n", raiz->produto);
        imprime(raiz->esq, b+1);
    }
}