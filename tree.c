#include "stdio.h"
#include "stdlib.h"
#include "tree.h"
#include "string.h"

Node* EXTERNAL;
Node* createEXTERNAL(){
    Node* newNo = (Node*)malloc(sizeof(Node));
    if (!newNo)
    {
        return NULL;
    }
    newNo->cor = BLACK;
    newNo->dir = newNo->esq = NULL;
    strcmp(newNo->produto, "NULL");
    newNo->qtd_produto = 0;
    return newNo;
}

Node* criar_no(char* produto, int quantidade) {
    Node* no = malloc(sizeof(Node));
    strcpy(no->produto, produto);
    no->cor = RED; // New nodes are initially red
    no->esq = no->dir = EXTERNAL;
    no->qtd_produto = quantidade;
    return no;
}

int isRed(Node* x) {
    if (x == NULL) return 0;
    return x->cor == RED;
}

Node* find_sucessor(Node* rbt)
{
    if (!rbt || rbt == EXTERNAL) return EXTERNAL;
    if (!rbt->esq || rbt->esq == EXTERNAL) return rbt;
    else find_sucessor(rbt->esq);
}

Node* get_pai(Node** raiz, Node* no)
{
    Node* pai = (*raiz);
    while (pai)
    {
        if (strcmp(pai->produto, no->produto) == 0)
            return EXTERNAL;
        else if (pai->dir && strcmp(pai->dir->produto, no->produto) == 0)
                return pai;
        else if (pai->esq && strcmp(pai->esq->produto, no->produto) == 0)
                return pai;
            
        else if (strcmp(pai->produto, no->produto) > 0)
            pai = pai->esq;
        else pai = pai->dir;
    }
}

void transfere_pai(Node** raiz, Node* rbt, Node* target)
{
    Node* paiRBT = get_pai(raiz, rbt);
    if (paiRBT == EXTERNAL)
        (*raiz) = target;
    else if (strcmp(paiRBT->esq->produto, rbt->produto) == 0)
        paiRBT->esq = target;
    else paiRBT->dir = target;
    
}

void left(Node** raiz, Node* pivo)
{
    Node* y = pivo->dir;
    Node* paiPivo = get_pai(&(*raiz), pivo);

    pivo->dir = y->esq;
    if (pivo->dir != EXTERNAL)
        paiPivo->dir = pivo;
    if (paiPivo == EXTERNAL)
        (*raiz) = y;
    else if (strcmp(pivo->produto, paiPivo->esq->produto) == 0)
        paiPivo->esq = y;
    else 
        paiPivo->dir = y;
    y->esq = pivo;
}

void right(Node** raiz, Node* pivo)
{
    Node* y = pivo->esq;
    Node* paiPivo = get_pai(&(*raiz), pivo);

    pivo->esq = y->dir;
    if (pivo->dir != EXTERNAL)
        paiPivo->esq = pivo;
    if (paiPivo == EXTERNAL)
        (*raiz) = y;
    else if (strcmp(pivo->produto, paiPivo->esq->produto) == 0)
        paiPivo->esq = y;
    else 
        paiPivo->dir = y;
    y->dir = pivo;
}

void deleteFixup(Node** raiz, Node* rbt, Node* pai)
{
    Node* siblingRbt;
    // O loop se repete ate que a cor preta extra deixa de existir.
    while (rbt != (*raiz) && rbt->cor == BLACK)
    {
        // Caso rbt seja filho a esquerda de seu pai.
        if (rbt == pai->esq){
            siblingRbt = pai->dir;
            // Caso 1: O irmao de rbt eh vermelho.
            if (siblingRbt->cor == RED){
                siblingRbt->cor = BLACK;
                pai->cor = RED;
                left(raiz, pai);
                siblingRbt = pai->dir;
            }
            // Caso 2: O irmao de rbt eh negro e os 2 filhos deste irmao tambem sao negros.
            if (siblingRbt->esq->cor == BLACK && siblingRbt->dir->cor == BLACK){
                siblingRbt->cor = RED;
                rbt = pai;
            }

            else{
                 if (siblingRbt->dir->cor == BLACK){
                    // Caso 3: O irmao de rbt eh negro,
                    // e este irmao tem filho a esquerda vermelho e filho a direita negro.
                    siblingRbt->esq->cor = BLACK;
                    siblingRbt->cor = RED;
                    right(raiz, siblingRbt);
                    siblingRbt = pai->dir;
                }
                // Caso 4: O irmao de rbt eh negro,
                // e este irmao tem filho a direita vermelho.
                siblingRbt->cor = pai->cor;
                pai->cor = BLACK;
                siblingRbt->dir->cor = BLACK;
                left(raiz, pai);
                // Para sair do loop.
                rbt = (*raiz);
            }
        }
        // Caso rbt seja filho a direita de seu pai.
        else {
            siblingRbt = pai->esq;
            // Caso 1: O irmao de rbt eh vermelho.
            if (siblingRbt->cor == RED){

                siblingRbt->cor = BLACK;
                pai->cor = RED;
                right(raiz, pai);
                siblingRbt = pai->esq;
            }
            // Caso 2: O irmao de rbt eh negro e os 2 filhos deste irmao tambem sao negros.
            if (siblingRbt->esq->cor == BLACK && siblingRbt->dir->cor == BLACK){
                siblingRbt->cor = RED;
                rbt = pai;
            }

            else{
                // Caso 3: O irmao de rbt eh negro,
                // e este irmao tem filho a direita vermelho e filho a esquerda negro.
                 if (siblingRbt->esq->cor == BLACK){
  
                    siblingRbt->dir->cor = BLACK;
                    siblingRbt->cor = RED;
                    left(raiz, siblingRbt);
                    siblingRbt = pai->esq;
                }
                // Caso 4: O irmao de rbt eh negro,
                // e este irmao tem filho a esquerda vermelho.
                siblingRbt->cor = pai->cor;
                pai->cor = BLACK;
                siblingRbt->esq->cor = BLACK;
                right(raiz, pai);
                // Para sair do loop.
                rbt = (*raiz);
            }
        }
    }
    rbt->cor = BLACK;
}

void remocao(Node** raiz, Node* delete)
{
    if (!(*raiz) || !delete) return;
    Node* auxSucessor;
    Node* sucessor = delete;
    Cor originalCor = sucessor->cor;
    Node* pai;
    if (delete->esq == EXTERNAL) 
    {
        pai = get_pai(&(*raiz), delete);
        auxSucessor = delete->dir;
        transfere_pai(&(*raiz), delete, delete->dir);
    }
    else if (delete->dir == EXTERNAL)
    {
        pai = get_pai(&(*raiz), delete);
        auxSucessor = delete->esq;
        transfere_pai(&(*raiz), delete, delete->esq);
    }
    else
    {
        sucessor = find_sucessor(delete->dir);
        originalCor = sucessor->cor;
        auxSucessor = sucessor->dir;
        Node* paiSucessor = get_pai(&(*raiz), sucessor);
        pai = paiSucessor;
        if (paiSucessor != EXTERNAL && (paiSucessor->produto, delete->produto) == 0)
        {
            pai = sucessor;
        }
        else
        {
            transfere_pai(&(*raiz), sucessor, sucessor->dir);
            sucessor->dir = delete->dir;
        }
        transfere_pai(&(*raiz), delete, sucessor);
        sucessor->esq = delete->esq;
        sucessor->cor = delete->cor;
    }
    if (originalCor == BLACK)
    {
        deleteFixup(raiz, auxSucessor, pai);
    }
}

Node* insert(Node* h, char* produto, int quantidade) {

    if (h == EXTERNAL) {
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

int verificaSeExiste(Node* raiz, char* produto)
{
    if (raiz == EXTERNAL) return 0;
    int tam = strcmp(produto, raiz->produto);
    while(raiz != EXTERNAL) { 
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

void imprime(Node* raiz, int b)
{
    if (raiz != EXTERNAL)
    {
        imprime(raiz->dir, b+1);
        for (int i = 0; i < b; i++) printf("      ");
        raiz->cor == RED ? printf("RED %s\n", raiz->produto) : printf("BLACK %s\n", raiz->produto);
        imprime(raiz->esq, b+1);
    }
}

Node* busca(Node* raiz, char* produto)
{
    if (raiz == EXTERNAL) return NULL;
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

void printEstoque(Node* h) {
    if (h != NULL) { 
        printEstoque(h->esq);
        if (h->qtd_produto > 0) {
            printf(" %s (%d) |", h->produto, h->qtd_produto);
        }
        printEstoque(h->dir);
    }
    printf("\n");
}

void printTreeHelper(Node* h) {
    if (h != EXTERNAL) { 
        printTreeHelper(h->esq);
        printf(" %s (%d) |", h->produto, h->qtd_produto);
        printTreeHelper(h->dir);
    }
    printf("\n");
}