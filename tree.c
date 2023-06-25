#include "stdio.h"
#include "stdlib.h"
#include "tree.h"
#include "string.h"


Node* criar_no(char* produto, int quantidade)
{
    Node* no = malloc(sizeof(Node));
    no->cor = BLACK;
    no->esq = NULL;
    no->dir = NULL;
    strcpy(no->produto, produto);
    no->qtd_produto = quantidade;
    return no;
}

void imprime(Node* raiz, int b)
{
    if (raiz)
    {
        imprime(raiz->dir, b+1);
        for (int i = 0; i < b; i++) printf("      ");
        printf("%s = %d\n", raiz->produto, raiz->qtd_produto);
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

int isRed(Node* node) {
    if (node == NULL)
        return 0;

    return (node->cor == RED);
}

void swapColors(Node* node1, Node* node2) {
    Cor temp = node1->cor;
    node1->cor = node2->cor;
    node2->cor = temp;
}

Node* rotateLeft(Node* node) {
    Node* newParent = node->dir;
    node->dir = newParent->esq;
    newParent->esq = node;
    return newParent;
}

Node* rotateRight(Node* node) {
    Node* newParent = node->esq;
    node->esq = newParent->dir;
    newParent->dir = node;
    return newParent;
}

Node* insertNode(Node* raiz, char* produto) {
    if (raiz == NULL)
        return criar_no(produto, 100);

    // Inserção do nó seguindo as regras da árvore Red-Black
    int tam = strcmp(produto, raiz->produto);
    if (tam < 0) {
        raiz->esq = insertNode(raiz->esq, produto);
    } else if (tam > 0) {
        raiz->dir = insertNode(raiz->dir, produto);
    } else {
        // Caso a chave já exista, não é permitida a inserção
        printf("Chave duplicada! Não é possível inserir.\n");
        return raiz;
    }

    // Verificações e ajustes necessários após a inserção
    if (isRed(raiz->dir) && !isRed(raiz->esq))
        raiz = rotateLeft(raiz);

    if (isRed(raiz->esq) && isRed(raiz->esq->esq))
        raiz = rotateRight(raiz);

    if (isRed(raiz->esq) && isRed(raiz->dir))
        swapColors(raiz, raiz->esq);

    return raiz;
}