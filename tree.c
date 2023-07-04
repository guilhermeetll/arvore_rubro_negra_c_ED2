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


Node* insert(Node* h, char* produto, int quantidade) {

    if (h == NULL) {
        return criar_no(produto, quantidade);
    }
    
    int cmp = strcmp(produto, h->produto);
    
    if (cmp < 0) {
        h->esq = insert(h->esq, produto, quantidade);
    } else if (cmp > 0) {
        h->dir = insert(h->dir, produto, quantidade);
    }

    return h;
}

Node* insertRoot(Node* root, char* produto, int quantidade) {

    int existe = verificaSeExiste(root, produto);

    if (existe == 1) {
        printf("\nProduto ja existente, adicione outro\n");
        return root;
    }

    root = insert(root, produto, quantidade);

    FPTA* familia = returnFamilia(root, produto);
    if (familia->avo != NULL) {
        FPTA* familia_old = returnFamilia(root, familia->pai->produto);
    }
    FPTA* familia_aux;
    Node* bisavo;

    // Rotações e recolorações para manter as propriedades da árvore Rubro-Negra
    while (familia->avo != NULL) { // Se o pai é vermelho
        // Caso do tio ser vermelho e pai tambem vermelho
        if (isRed(familia->tio) && isRed(familia->pai) && isRed(familia->filho)){
            familia->pai->cor = BLACK;
            familia->tio->cor = BLACK;
            familia->avo->cor = RED;
            familia = returnFamilia(root, familia->avo->produto);

        // Caso nao tenha mudanças
        } else {
            // Rotacao a esquerda CASO 2 Caso Dificil
            if ((familia->avo->esq == familia->pai) && (familia->filho == familia->pai->dir) && 
                (familia->filho->cor == RED) && (familia->pai->cor == RED)) {
                familia->pai->dir = familia->filho->esq;
                familia->filho->esq = familia->pai;
                familia->avo->esq = familia->filho;
                familia = returnFamilia(root, familia->pai->produto);
                familia->avo->esq = familia->pai->dir;
                familia->pai->dir = familia->avo;
                familia->pai->cor = BLACK;
                familia->avo->cor = RED;
                if (root == familia->avo) {
                    root = familia->pai;
                }
                familia = returnFamilia(root, familia->pai->produto);

            // Rotacao a direita CASO 2 Caso dificil
            } else if ((familia->avo->dir == familia->pai) && (familia->filho == familia->pai->esq) && 
                (familia->filho->cor == RED) && (familia->pai->cor == RED)) {
                familia->pai->esq = familia->filho->dir;
                familia->filho->dir = familia->pai;
                familia->avo->dir = familia->filho;
                familia = returnFamilia(root, familia->pai->produto);
                familia->avo->dir = familia->pai->esq;
                familia->pai->esq = familia->avo;
                familia->pai->cor = BLACK;
                familia->avo->cor = RED;
                if (root == familia->avo) {
                    root = familia->pai;
                }
                familia = returnFamilia(root, familia->pai->produto);

            // Rotacao a direita CASO 1 Caso Facil
            } else if ((familia->avo->esq == familia->pai) && (familia->filho == familia->pai->esq) && 
                (familia->filho->cor == RED) && (familia->pai->cor == RED)) {
                familia_aux = returnFamilia(root, familia->pai->produto);
                bisavo = familia_aux->avo;
                if (bisavo != NULL) {
                    if (bisavo->esq == familia->avo) {
                        bisavo->esq = familia->pai;
                    } else {
                        bisavo->dir = familia->pai;
                    }
                    familia->avo->esq = familia->pai->dir;
                    familia->pai->dir = familia->avo;
                } else {
                    root = familia->pai;
                    familia->avo->esq = familia->pai->dir;
                    familia->pai->dir = familia->avo;
                }
                familia->pai->cor = BLACK;
                familia->avo->cor = RED;
                if (root == familia->avo) {
                    root = familia->pai;
                }
                familia = returnFamilia(root, familia->pai->produto);

            // Esse eu nao sei se esta certo
            } else if ((familia->avo->dir == familia->pai) && (familia->filho == familia->pai->dir) && 
                (familia->filho->cor == RED) && (familia->pai->cor == RED)) {
                familia_aux = returnFamilia(root, familia->pai->produto);
                bisavo = familia_aux->avo;
                if (bisavo != NULL) {
                    if (bisavo->dir == familia->avo) {
                        bisavo->dir = familia->pai;
                    } else {
                        bisavo->esq = familia->pai;
                    }
                    familia->avo->dir = familia->pai->esq;
                    familia->pai->esq = familia->avo;
                } else {
                    root = familia->pai;
                    familia->avo->dir = familia->pai->esq;
                    familia->pai->esq = familia->avo;
                }
                familia->pai->cor = BLACK;
                familia->avo->cor = RED;
                if (root == familia->avo) {
                    root = familia->pai;
                }
                familia = returnFamilia(root, familia->pai->produto);

            } else {
                familia = returnFamilia(root, familia->pai->produto);
            }
        }
    }

    root->cor = BLACK; // Garante que a raiz é sempre preta
    return root;
}

void imprime(Node* raiz, int b) {
    if (raiz) {
        imprime(raiz->dir, b + 1);
        for (int i = 0; i < b; i++) printf("          ");
        printf("(%s(%d) %s)\n", raiz->produto, raiz->qtd_produto, raiz->cor == RED ? "RED" : "BLACK");
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

int verificaSeExiste(Node* raiz, char* produto)
{
    if (raiz == NULL) return 0;
    int tam = strcmp(produto, raiz->produto);
    while(raiz != NULL) { 
        tam = strcmp(produto, raiz->produto);
        if (tam == 0)
        {
            return 1;
        }
        else if (tam > 0)
        {
            raiz = raiz->dir;
        }
        else if (tam < 0)
        {
            raiz = raiz->esq;
        }
    }
    return 0;
}

void printTreeHelper(Node* h) {
    if (h != NULL) { 
        printTreeHelper(h->esq);
        printf(" %s (%d) |", h->produto, h->qtd_produto);
        printTreeHelper(h->dir);
    }
}

void printEstoque(Node* h) {
    if (h != NULL) { 
        printEstoque(h->esq);
        if (h->qtd_produto > 0) {
            printf(" %s (%d) |", h->produto, h->qtd_produto);
        }
        printEstoque(h->dir);
    }
}
