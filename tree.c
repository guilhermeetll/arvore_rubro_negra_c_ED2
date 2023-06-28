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

            } else {
                familia->avo = familia->pai;
                familia->pai = familia->filho;
            }
            if (familia->avo != NULL) {
                if ((familia->avo->dir != NULL) && (familia->avo->esq != NULL)) {

                    if (familia->avo->dir != NULL) {
                        if (strcmp(familia->avo->dir->produto, familia->pai->produto) == 0) {
                            familia->tio = familia->avo->esq;
                        }
                    } 

                    if (familia->avo->esq != NULL) {
                        if (strcmp(familia->avo->esq->produto, familia->pai->produto) == 0) {
                            familia->tio = familia->avo->dir;
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

            } else {
                familia->avo = familia->pai;
                familia->pai = familia->filho;
            }
            if (familia->avo != NULL) {
                if ((familia->avo->dir != NULL) && (familia->avo->esq != NULL)) {

                    if (familia->avo->dir != NULL) {
                        if (strcmp(familia->avo->dir->produto, familia->pai->produto) == 0) {
                            familia->tio = familia->avo->esq;
                        }
                    }

                    if (familia->avo->esq != NULL) {
                        if (strcmp(familia->avo->esq->produto, familia->pai->produto) == 0) {
                            familia->tio = familia->avo->dir;
                        }
                    }
                } else if ((familia->avo->dir == NULL) || (familia->avo->esq == NULL)) {
                    familia->tio = NULL;
                }
            }
            familia->filho = familia->filho->dir;
        }
    }
    return familia;
}

int swapCor(Node* x) {
    if (isRed(x) == 1) {
        return BLACK;
    } else {
        return RED;
    }
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

    return h;
}

Node* insertRoot(Node* root, char* produto) {
    root = insert(root, produto);

    FPTA* familia     = returnFamilia(root, produto);
    FPTA* familia_pai = returnFamilia(root, familia->pai->produto);
    Node* Bisavo      = familia_pai->avo;
    
    printf("\nRotacao simples");
    printf("\nFilho = %s", familia->filho->produto);
    printf("\nPai   = %s", familia->pai->produto);
    printf("\nTio   = %s", familia->tio->produto);
    printf("\nAvo   = %s", familia->avo->produto);
    printf("\nTatara= %s", Bisavo->produto);
    if ((familia->tio == NULL) && (familia->avo != NULL)) {

        // Rotacao simples
        if (strcmp(familia->filho->produto, familia->pai->esq->produto) == 0) {
            printf("\nRotacao simples");
            printf("\nFilho = %s", familia->filho->produto);
            printf("\nPai   = %s", familia->pai->produto);
            printf("\nTio   = %s", familia->tio->produto);
            printf("\nAvo   = %s", familia->avo->produto);
            printf("\nTatara= %s", Bisavo->produto);
            familia->avo->dir = criar_no(familia->avo->produto, familia->avo->qtd_produto);
            strcpy(familia->avo->produto, familia->avo->esq->produto);
            familia->avo->qtd_produto = familia->avo->esq->qtd_produto;
            familia->avo->esq = familia->filho;
            familia = returnFamilia(root, produto);
        }

        // Rotacao dupla
        if (strcmp(familia->filho->produto, familia->pai->dir->produto) == 0) {
            printf("\nRotacao dupla");
            printf("\nFilho = %s", familia->filho->produto);
            printf("\nPai   = %s", familia->pai->produto);
            printf("\nTio   = %s", familia->tio->produto);
            printf("\nAvo   = %s", familia->avo->produto);
            familia->avo->dir = criar_no(familia->avo->produto, familia->avo->qtd_produto);
            strcpy(familia->avo->produto, familia->filho->produto);
            familia->avo->qtd_produto = familia->filho->qtd_produto;
            familia->pai->esq = NULL;
            familia = returnFamilia(root, produto);
        }
        
    } else if (familia->tio != NULL) {
        if (familia->tio->cor == RED) {
            while ((isRed(familia->pai) == 1) && (isRed(familia->filho) == 1)) {
                familia->pai->cor = BLACK;
                if (familia->avo != NULL) {
                    familia->avo->cor = RED;
                } 
                if (familia->tio != NULL) {
                    familia->tio->cor = BLACK;
                }
                familia = returnFamilia(root, familia->avo->produto);
            }
        }
    }

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