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




Node* find_sucessor(Node** rbt)
{
    if (!rbt) return NULL;
    if (!(*rbt)->esq) return (*rbt);
    else find_sucessor(&(*rbt)->esq);
}

Node* get_pai(Node** raiz, Node** no)
{
    Node* pai = (*raiz);
    while (pai)
    {
        if (strcmp(pai->produto, (*no)->produto) == 0)
            return NULL;
        else if (pai->dir && strcmp(pai->dir->produto, (*no)->produto) == 0)
                return pai;
        else if (pai->esq && strcmp(pai->esq->produto, (*no)->produto) == 0)
                return pai;
            
        else if (strcmp(pai->produto, (*no)->produto) > 0)
            pai = pai->esq;
        else pai = pai->dir;
    }
}

void transfere_pai(Node** raiz, Node** pai, Node** neto)
{
    Node* filho = get_pai(&(*raiz), &(*neto));
    filho = get_pai(&(*raiz), &filho);
    if (!(*pai)) (*raiz) = (*neto);
    else if ((*pai)->esq && strcmp(filho->produto, (*pai)->esq->produto) == 0)
    {
        (*pai)->esq = (*neto);
    }
    else 
        (*pai)->dir = (*neto);
}
void remocao(Node** raiz, Node** pai, Node** delete)
{   
    if (!(*raiz) || !delete) return;
    Node* deleted = (*delete);
    Node* auxSucessor;
    Node* sucessor = (*delete);
    Cor originalCor = sucessor->cor;

    if (!(*delete)->esq && !(*delete)->esq) 
    {
        if (strcmp((*raiz)->produto, (*delete)->produto) == 0) 
        {
            (*raiz) = NULL;
        }
        else if ((*pai)->esq && strcmp((*pai)->esq->produto, (*delete)->produto) == 0) (*pai)->esq = NULL;
        else (*pai)->dir = NULL;
    }
    else if (!(*delete)->esq)
    {
        auxSucessor = (*delete)->dir;
        transfere_pai(&(*raiz), &(*pai), &(*delete)->dir);
    }
    else if (!(*delete)->dir)
    {  
        auxSucessor = (*delete)->esq;
        transfere_pai(&(*raiz), &(*pai), &(*delete)->esq);
    }
    else 
    {
        sucessor = find_sucessor(&(*delete)->dir);
        originalCor = sucessor->cor;
        auxSucessor = sucessor->dir;

        if (strcmp((*delete)->dir->produto, sucessor->produto) == 0)
            (*pai)->dir = sucessor;
        else 
        {   
            Node* paiSucessor = get_pai(&(*raiz), &sucessor);
            transfere_pai(&(*raiz), &(*pai), &sucessor);
            sucessor->dir = (*delete)->dir;
            if (paiSucessor->dir && strcmp(paiSucessor->dir->produto, sucessor->produto) == 0) paiSucessor->dir = NULL;
            else paiSucessor->esq = NULL;
        }
        //transfere_pai(&(*raiz), &(*pai), &sucessor);
        sucessor->esq = (*delete)->esq;
        sucessor->cor = (*delete)->cor;
    }
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