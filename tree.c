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

FPTA* returnFamilia(Node* raiz, char* produto) {
    FPTA* familia = malloc(sizeof(FPTA));
    familia->filho = raiz;
    familia->pai = NULL;
    familia->avo = NULL;
    familia->tio = NULL;

    while (familia->filho && strcmp(produto, familia->filho->produto) != 0) {
        int cmp = strcmp(produto, familia->filho->produto);

        if (cmp < 0) {
            if (familia->pai == NULL) {
                familia->pai = familia->filho;

            } else if (familia->avo == NULL) {
                familia->avo = familia->pai;
                familia->pai = familia->filho;

                if ((familia->avo->dir != NULL) && (familia->avo->esq != NULL)) {

                    if (familia->avo->dir != NULL) {
                        if (strcmp(familia->avo->esq->produto, familia->pai->produto) == 0) {
                            familia->tio = familia->avo->dir;
                        }
                    } 

                    if (familia->avo->esq != NULL) {
                        if (strcmp(familia->avo->dir->produto, familia->pai->produto) == 0) {
                            familia->tio = familia->avo->esq;
                        }
                    }
                }
            }
            familia->filho = familia->filho->esq;

        } else if (cmp > 0) {
            if (familia->pai == NULL) {
                familia->pai = familia->filho;

            } else if (familia->avo == NULL) {
                familia->avo = familia->pai;
                familia->pai = familia->filho;

                if ((familia->avo->dir != NULL) && (familia->avo->esq != NULL)) {

                    if (familia->avo->dir != NULL) {
                        if (strcmp(familia->avo->esq->produto, familia->pai->produto) == 0) {
                            familia->tio = familia->avo->dir;
                        }
                    } 
                    
                    if (familia->avo->esq != NULL) {
                        if (strcmp(familia->avo->dir->produto, familia->pai->produto) == 0) {
                            familia->tio = familia->avo->esq;
                        }
                    }
                }
            }
            familia->filho = familia->filho->dir;
        }
    }
    return familia;
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

    FPTA* familia = returnFamilia(h, produto);


    return h;
}

Node* insertRoot(Node* root, char* produto) {
    root = insert(root, produto);
    root->cor = BLACK; // Ensure the root is always black
    return root;
}

void imprime(Node* raiz, int b) {
    if (raiz) {
        imprime(raiz->dir, b + 1);
        for (int i = 0; i < b; i++) printf("            ");
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