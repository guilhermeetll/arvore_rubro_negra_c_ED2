#include "stdio.h"
#include "stdlib.h"
#include "tree.h"
#include "string.h"



Node* criar_no(char* produto)
{
    Node* no = malloc(sizeof(Node));
    no->cor = BLACK;
    no->esq = NULL;
    no->dir = NULL;
    strcpy(no->produto, produto);
    no->qtd_produto = 0;
    return no;
}

void remocao(Node** raiz, char* produto)
{
    
}

void insert_no(Node** raiz, char* produto)
{
    if (*raiz == NULL)
    {
        *raiz = criar_no(produto);
        (*raiz)->cor = RED;
        return;
    }
    int tam = strcmp((*raiz)->produto, produto);
    if (tam < 0) {return insert_no(&(*raiz)->dir, produto);}
    else if (tam > 0) {return insert_no(&(*raiz)->esq, produto);}
    else if (tam == 0) 
    {
        printf("O produto já está cadastrado.\n");
    }
}

void imprime(Node* raiz, int b)
{
    if (raiz)
    {
        imprime(raiz->dir, b+1);
        for (int i = 0; i < b; i++) printf("      ");
        // raiz->cor == RED ? printf("RED\n") : printf("BLACK\n");
        printf("%s\n", raiz->produto);
        imprime(raiz->esq, b+1);
    }
}
Node* busca(Node* raiz, char* produto)
{
    if (raiz == NULL) return NULL;
    int tam = strcmp(produto, raiz->produto);
    if (tam == 0)
    {
        return raiz;
    }
    else if (tam > 0)
    {
        busca(raiz->dir, produto);
    }
    else if (tam < 0)
    {
        busca(raiz->esq, produto);
    }
    
}

