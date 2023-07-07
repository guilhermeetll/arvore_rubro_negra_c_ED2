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

Node* criar_no(char* produto)
{
    Node* no = malloc(sizeof(Node));
    no->cor = BLACK;
    no->esq = EXTERNAL;
    no->dir = EXTERNAL;
    strcpy(no->produto, produto);
    no->qtd_produto = 0;
    return no;
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
        printf("%s\n", sucessor->produto);
    }
    if (originalCor == BLACK)
    {
        deleteFixup(raiz, auxSucessor, pai);
    }
}

void insert_no(Node** raiz, char* produto)
{
    if (*raiz == EXTERNAL)
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