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

int isRed(Node* x) 
{
    if (x == NULL) return 0;
    return x->cor == RED;
}

Node* find_sucessor(Node* rbt)
{
    /* 
        Função resposável por capturar o sucessor de um nó removido 
        
        Args: 
            rbt (Node), nó que vai ser deletado.

        Returns: 
            nó sucessor ou nó EXTERNAL.

    */
    if (!rbt || rbt == EXTERNAL) return EXTERNAL;
    if (!rbt->esq || rbt->esq == EXTERNAL) return rbt;
    else find_sucessor(rbt->esq);
}

Node* get_pai(Node** raiz, Node* no)
{
    /*
        Função que busca o nó "pai" de outro nó.

        Args: 
            raiz (Node): raiz da árvore;
            no (Node): Nó que se dejesa buscar o pai;

        Returns:
            External, caso o nó seja a raiz;
            Nó antecessor do nó passado;
    */
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
    /*
        Função responsável por transferir a referência de
        um node para pai para o filho do nó deletado.

        Args: 
            raiz (Node): raiz da árvore.
            rbt (Node): nó deletado.
            target (Node): filho do nó deletado.
        
        Returns:
            sem retornos.
    */
    Node* paiRBT = get_pai(raiz, rbt);
    if (paiRBT == EXTERNAL)
        (*raiz) = target;
    else if (strcmp(paiRBT->esq->produto, rbt->produto) == 0)
        paiRBT->esq = target;
    else paiRBT->dir = target;
    
}

void left(Node** raiz, Node* pivo)
{
    /**
     * Realiza uma rotação para a esquerda em uma árvore binária de busca.
     *
     * @param raiz Um ponteiro para um ponteiro para o nó raiz da árvore.
     * @param pivo O nó que será o pivô da rotação.
     */
    Node* y = pivo->dir; // Armazena o nó à direita do pivô como 'y'
    Node* paiPivo = get_pai(&(*raiz), pivo); // Obtém o pai do pivô na árvore

    pivo->dir = y->esq; // O filho à esquerda de 'y' se torna o filho à direita do pivô

    // Atualiza o pai do pivô para apontar para o pivô atualizado
    if (pivo->dir != EXTERNAL) // Se o filho à direita do pivô não for um nó externo
        paiPivo->dir = pivo;

    if (paiPivo == EXTERNAL) // Se o pai do pivô for um nó externo, significa que o pivô era a raiz
        (*raiz) = y; // Atualiza a raiz para apontar para 'y'
    else if (strcmp(pivo->produto, paiPivo->esq->produto) == 0) // Se o pivô for filho esquerdo do pai
        paiPivo->esq = y; // Atualiza o filho esquerdo do pai para apontar para 'y'
    else 
        paiPivo->dir = y; // Caso contrário, atualiza o filho direito do pai para apontar para 'y'

    y->esq = pivo; // O pivô se torna filho esquerdo de 'y'
}

void right(Node** raiz, Node* pivo)
{
    /**
     * Realiza uma rotação para a direita em uma árvore binária de busca.
     *
     * @param raiz Um ponteiro para um ponteiro para o nó raiz da árvore.
     * @param pivo O nó que será o pivô da rotação.
     */
    Node* y = pivo->esq; // Armazena o nó à esquerda do pivô como 'y'
    Node* paiPivo = get_pai(&(*raiz), pivo); // Obtém o pai do pivô na árvore

    pivo->esq = y->dir; // O filho à direita de 'y' se torna o filho à esquerda do pivô

    // Atualiza o pai do pivô para apontar para o pivô atualizado
    if (pivo->dir != EXTERNAL) // Se o filho à direita do pivô não for um nó externo
        paiPivo->esq = pivo;

    if (paiPivo == EXTERNAL) // Se o pai do pivô for um nó externo, significa que o pivô era a raiz
        (*raiz) = y; // Atualiza a raiz para apontar para 'y'
    else if (strcmp(pivo->produto, paiPivo->esq->produto) == 0) // Se o pivô for filho esquerdo do pai
        paiPivo->esq = y; // Atualiza o filho esquerdo do pai para apontar para 'y'
    else 
        paiPivo->dir = y; // Caso contrário, atualiza o filho direito do pai para apontar para 'y'

    y->dir = pivo; // O pivô se torna filho direito de 'y'
}

void deleteFixup(Node** raiz, Node* rbt, Node* pai)
{
    /**
     * Realiza a correção após a remoção de um nó em uma árvore rubro-negra.
     *
     * @param raiz Um ponteiro para um ponteiro para o nó raiz da árvore.
     * @param rbt O nó que foi removido da árvore.
     * @param pai O pai do nó removido.
     */
    Node* siblingRbt;

    // O loop se repete até que a cor preta extra deixe de existir.
    while (rbt != (*raiz) && rbt->cor == BLACK)
    {
        // Caso rbt seja filho à esquerda de seu pai.
        if (rbt == pai->esq){
            siblingRbt = pai->dir;

            // Caso 1: O irmão de rbt é vermelho.
            if (siblingRbt->cor == RED){
                siblingRbt->cor = BLACK;
                pai->cor = RED;
                left(raiz, pai);
                siblingRbt = pai->dir;
            }

            // Caso 2: O irmão de rbt é negro e os dois filhos deste irmão também são negros.
            if (siblingRbt->esq->cor == BLACK && siblingRbt->dir->cor == BLACK){
                siblingRbt->cor = RED;
                rbt = pai;
            }

            else{
                 if (siblingRbt->dir->cor == BLACK){
                    // Caso 3: O irmão de rbt é negro
                    // e este irmão tem filho à esquerda vermelho e filho à direita negro.
                    siblingRbt->esq->cor = BLACK;
                    siblingRbt->cor = RED;
                    right(raiz, siblingRbt);
                    siblingRbt = pai->dir;
                }

                // Caso 4: O irmão de rbt é negro
                // e este irmão tem filho à direita vermelho.
                siblingRbt->cor = pai->cor;
                pai->cor = BLACK;
                siblingRbt->dir->cor = BLACK;
                left(raiz, pai);

                // Para sair do loop.
                rbt = (*raiz);
            }
        }
        // Caso rbt seja filho à direita de seu pai.
        else {
            siblingRbt = pai->esq;

            // Caso 1: O irmão de rbt é vermelho.
            if (siblingRbt->cor == RED){
                siblingRbt->cor = BLACK;
                pai->cor = RED;
                right(raiz, pai);
                siblingRbt = pai->esq;
            }

            // Caso 2: O irmão de rbt é negro e os dois filhos deste irmão também são negros.
            if (siblingRbt->esq->cor == BLACK && siblingRbt->dir->cor == BLACK){
                siblingRbt->cor = RED;
                rbt = pai;
            }

            else{
                // Caso 3: O irmão de rbt é negro
                // e este irmão tem filho à direita vermelho e filho à esquerda negro.
                if (siblingRbt->esq->cor == BLACK){
                    siblingRbt->dir->cor = BLACK;
                    siblingRbt->cor = RED;
                    left(raiz, siblingRbt);
                    siblingRbt = pai->esq;
                }

                // Caso 4: O irmão de rbt é negro
                // e este irmão tem filho à esquerda vermelho.
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
    /**
     * Realiza a remoção de um nó em uma árvore binária de busca rubro-negra.
     *
     * @param raiz Um ponteiro para um ponteiro para o nó raiz da árvore.
     * @param delete O nó que será removido da árvore.
     */
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

        if (paiSucessor != EXTERNAL && strcmp(paiSucessor->produto, delete->produto) == 0)
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
    /**
     * Imprime os nós de uma árvore binária de busca rubro-negra.
     *
     * @param raiz O nó raiz da árvore.
     * @param b O nível de recuo para formatar a impressão.
     */
    if (raiz != EXTERNAL)
    {
        // Imprime os nós da subárvore direita primeiro (percurso em ordem decrescente)
        imprime(raiz->dir, b+1);

        // Adiciona recuo para formatar a impressão
        for (int i = 0; i < b; i++)
            printf("      ");

        // Imprime o nó atual, exibindo sua cor e produto
        raiz->cor == RED ? printf("RED %s\n", raiz->produto) : printf("BLACK %s\n", raiz->produto);

        // Imprime os nós da subárvore esquerda
        imprime(raiz->esq, b+1);
    }
}

Node* busca(Node* raiz, char* produto)
{
    /**
     * Realiza uma busca por um nó em uma árvore binária de busca rubro-negra.
     *
     * @param raiz O nó raiz da árvore.
     * @param produto O produto a ser buscado.
     * @return Um ponteiro para o nó encontrado ou NULL se não for encontrado.
     */
    if (raiz == EXTERNAL) return NULL;

    int tam = strcmp(produto, raiz->produto);

    if (tam == 0)
    {
        return raiz; // Retorna o nó encontrado
    }
    else if (tam > 0)
    {
        return busca(raiz->dir, produto); // Realiza a busca na subárvore direita
    }
    else if (tam < 0)
    {
        return busca(raiz->esq, produto); // Realiza a busca na subárvore esquerda
    }
    
    // Caso nenhuma das condições anteriores seja satisfeita, retorna NULL (nó não encontrado)
    return NULL;
}

void printEstoque(Node* h) {
    /**
     * Imprime o estoque de produtos representado por uma árvore binária.
     *
     * @param h O nó raiz da árvore.
     */
    if (h != NULL) { 
        printEstoque(h->esq); // Imprime os nós da subárvore esquerda (percurso em ordem)
        
        if (h->qtd_produto > 0) {
            printf(" %s (%d) |", h->produto, h->qtd_produto); // Imprime o produto e a quantidade
        }
        
        printEstoque(h->dir); // Imprime os nós da subárvore direita
    }
    
    printf("\n"); // Imprime uma nova linha no final para melhorar a formatação
}

void printTreeHelper(Node* h) {
    /**
     * Função auxiliar para imprimir uma árvore binária representando o estoque de produtos.
     *
     * @param h O nó raiz da árvore.
     */
    if (h != EXTERNAL) { 
        printTreeHelper(h->esq); // Imprime os nós da subárvore esquerda (percurso em ordem)
        printf(" %s (%d) |", h->produto, h->qtd_produto); // Imprime o produto e a quantidade
        printTreeHelper(h->dir); // Imprime os nós da subárvore direita
    }
    printf("\n"); // Imprime uma nova linha no final para melhorar a formatação
}