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


void transfere_pai(Node** raiz, Node** pai, Node** neto)
{
    printf("%s %s\n", (*pai)->produto, (*raiz)->produto);
    if ((*raiz) == (*pai)->esq)
        (*pai)->esq = (*neto);
    else 
        (*pai)->dir = (*neto);
}
Node* sucessor(Node** raiz)
{
    Node* aux = (*raiz)->dir;
    Node* min = NULL;
    while (aux)
    {
        if (strcmp(aux->produto, "zzzz") < 0) 
        {
            min = aux;
        }
        aux = aux->esq;
    }
    return min;
    
}
void remocao(Node** raiz, Node** pai, char* produto)
{
    if (*raiz == NULL) return;
    if (strcmp((*raiz)->produto, produto) == 0)
    {
        Node *y,*x;
        int corY = (*raiz)->cor;
        if (!(*raiz)->esq) 
            transfere_pai(&(*raiz), &(*pai), &(*raiz)->dir);
        else if (!(*raiz)->dir)
                transfere_pai(&(*raiz), &(*pai), &(*raiz)->esq);
        else 
        {
            y = sucessor(&(*raiz));
            corY = y->cor;
            transfere_pai(&(*raiz), &(*pai), &y->dir);
            y->dir = (*raiz)->dir;
        }
        
        // if (!(*raiz)->esq && !(*raiz)->dir) // caso 1, não tem filhos
        //     *raiz = NULL;
        
        // else if ((*raiz)->esq || (*raiz)->dir)
        // {
        //     printf("%s %s\n",(*pai)->produto, (*raiz)->produto);
        //     if ((*raiz)->esq) 
        //     {
        //         if (strcmp((*pai)->produto, produto) > 0)
        //         {
        //             Node* x = (*raiz)->esq;
        //             (*raiz) = NULL;
        //             (*pai)->esq  = x;
        //         }
        //         else
        //         {
        //             Node* x = (*raiz)->esq;
        //             (*raiz) = NULL;
        //             (*pai)->dir  = x;
        //         }
        //     }
        //     else
        //     {
        //         if (strcmp((*pai)->produto, produto) > 0)
        //         {
        //             Node* x = (*raiz)->dir;
        //             (*raiz) = NULL;
        //             (*pai)->esq  = x;
        //         }
        //         else
        //         {
        //             Node* x = (*raiz)->dir;
        //             (*raiz) = NULL;
        //             (*pai)->dir  = x;
        //         }
        //     }
        // }
    
    }
    else if (strcmp((*raiz)->produto, produto) > 0)
        remocao(&(*raiz)->esq, &(*raiz), produto);
    else if (strcmp((*raiz)->produto, produto) < 0) 
        remocao(&(*raiz)->dir, &(*raiz), produto);
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
        raiz->cor == RED ? printf("RED %s\n", raiz->produto) : printf("BLACK %s\n", raiz->produto);
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

void lista_produtos(Node* raiz, int resp)
{
    if (raiz)
    {
        if (raiz->qtd_produto >= 0 && resp == 4) printf("| produto: %s\n", raiz->produto);
        else if (raiz->qtd_produto > 0 && resp == 5) printf("| produto: %s\n| quantidade: %d\n", raiz->produto, raiz->qtd_produto);
        lista_produtos(raiz->esq, resp);
        lista_produtos(raiz->dir, resp);
    }
}