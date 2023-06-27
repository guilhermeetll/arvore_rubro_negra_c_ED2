#include "stdio.h"
#include "stdlib.h"
#include "tree.h"
#include "string.h"


Node* criar_no(char* produto, int quantidade) {
    Node* no = malloc(sizeof(Node));
    strcpy(no->produto, produto);
    no->cor = RED; // New nodes are initially red
    no->esq = no->dir = NULL;
    no->qtd_produto = quantidade;
    return no;
}

int isRed(Node* x) {
    if (x == NULL) return 0;
    return x->cor == RED;
}

Node* rotateLeft(Node* h) {
    Node* x = h->dir;
    h->dir = x->esq;
    x->esq = h;
    x->cor = h->cor;
    h->cor = RED;
    return x;
}

Node* rotateRight(Node* h) {
    Node* x = h->esq;
    h->esq = x->dir;
    x->dir = h;
    x->cor = h->cor;
    h->cor = RED;
    return x;
}

void flipColors(Node* h) {
    h->cor = !h->cor;
    h->esq->cor = !h->esq->cor;
    h->dir->cor = !h->dir->cor;
}

Node* insert(Node* h, char* produto) {
    if (h == NULL) {
        return criar_no(produto, 100);
    }
    
    int cmp = strcmp(produto, h->produto);
    
    if (cmp < 0) {
        h->esq = insert(h->esq, produto);
    } else if (cmp > 0) {
        h->dir = insert(h->dir, produto);
    }

    // Fix-up to maintain Red-Black tree properties
    if (isRed(h->dir) && !isRed(h->esq)) h = rotateLeft(h);
    if (isRed(h->esq) && isRed(h->esq->esq)) h = rotateRight(h);
    if (isRed(h->esq) && isRed(h->dir)) flipColors(h);

    return h;
}

Node* insertRoot(Node* root, char* produto) {
    root = insert(root, produto);
    root->cor = BLACK; // root must always be black
    return root;
}

void imprime(Node* raiz, int b) {
    if (raiz) {
        imprime(raiz->dir, b + 1);
        for (int i = 0; i < b; i++) printf("    ");
        printf("%s (%s)\n", raiz->produto, raiz->cor == RED ? "RED" : "BLACK");
        imprime(raiz->esq, b + 1);
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