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

void rotateLeft(Node* h) {
    Node* x = h->esq;
    h->esq = h->esq->dir;
    h->esq = x;
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
    h->cor = swapCor(h);
    h->esq->cor = swapCor(h->esq);
    h->dir->cor = swapCor(h->dir);
}

Node* insertRoot(Node* root, char* produto) {
    root = insert(root, produto);
    
    FPTA* familia = returnFamilia(root, produto);
    
    // Rotações e recolorações para manter as propriedades da árvore Rubro-Negra
    while (isRed(familia->pai) && (familia->avo) && isRed(familia->filho)) { // Se o pai é vermelho

        // Caso 1: Tio é vermelho - Recoloração
        if (isRed(familia->tio)) {
            familia->avo->cor = RED;
            familia->pai->cor = BLACK;
            familia->tio->cor = BLACK;

        } else {
            // Caso 2: Tio é preto ou NULL - Rotações
            
            // Rotacao simples para esquerda
            if (familia->pai == familia->avo->dir && familia->filho == familia->pai->dir) {
                familia->avo->esq = criar_no(familia->avo->produto, 100);
                strcpy(familia->avo->produto, familia->pai->produto);
                familia->avo->qtd_produto = familia->pai->qtd_produto;
                familia->avo->dir = familia->filho;
                swapCor(familia->avo);

            // Rotacao dupla para esquerda
            } else if (familia->pai == familia->avo->dir && familia->filho == familia->pai->esq) {
                familia->filho->dir = familia->pai;
                familia->avo->dir = familia->filho;
                familia->pai->esq = NULL;

                familia->avo->esq = criar_no(familia->avo->produto, 100);
                strcpy(familia->avo->produto, familia->filho->produto);
                familia->avo->qtd_produto = familia->filho->qtd_produto;
                familia->avo->dir = familia->pai;
                swapCor(familia->avo);

            // Rotacao dupla para direita
            } else if (familia->pai == familia->avo->esq && familia->filho == familia->pai->dir) {
                familia->filho->esq = familia->pai;
                familia->avo->esq = familia->filho;
                familia->pai->dir = NULL;

                familia->avo->dir = criar_no(familia->avo->produto, 100);
                strcpy(familia->avo->produto, familia->filho->produto);
                familia->avo->qtd_produto = familia->filho->qtd_produto;
                familia->avo->esq = familia->pai;
                swapCor(familia->avo);

            // Rotacao simples para direita
            } else if (familia->pai == familia->avo->esq && familia->filho == familia->pai->esq) {
                familia->avo->dir = criar_no(familia->avo->produto, 100);
                strcpy(familia->avo->produto, familia->pai->produto);
                familia->avo->qtd_produto = familia->pai->qtd_produto;
                familia->avo->esq = familia->filho;
                swapCor(familia->avo);
            }
        }
        familia = returnFamilia(familia->avo, produto);
    }
    
    root->cor = BLACK; // Garante que a raiz é sempre preta
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