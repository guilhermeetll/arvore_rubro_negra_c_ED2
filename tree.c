/**
 * Grupo 7
 * Gabriela júlia Tavares Elias
 * Guilherme Travaglia Largura
 * Lucas Ferreira de Souza Santos
*/

#include "stdio.h"
#include "stdlib.h"
#include "tree.h"
#include "string.h"

// Criação de uma variável global "EXTERNAL" do tipo "Node*" para representar um nó externo na árvore.
Node* EXTERNAL;

Node* createEXTERNAL(){
    /**
     * Esta função cria um nó externo, que é usado para marcar o final de um ramo em uma árvore.
     *
     * @return O nó externo criado.
     */
    // Alocação de memória para o novo nó.
    Node* newNo = (Node*)malloc(sizeof(Node));

    // Verificação se a alocação de memória foi bem sucedida.
    if (!newNo)
    {
        return NULL;
    }

    // Definição das propriedades do nó externo: cor preta, sem filhos, produto "NULL" e quantidade 0.
    newNo->cor = BLACK;
    newNo->dir = newNo->esq = NULL;
    strcmp(newNo->produto, "NULL");
    newNo->qtd_produto = 0;

    // Retorna o nó externo.
    return newNo;
}

Node* criar_no(char* produto, int quantidade) {
    /**
     * Esta função cria um novo nó com um produto e quantidade especificados.
     *
     * @param produto O produto a ser inserido no nó.
     * @param quantidade A quantidade do produto a ser inserida no nó.
     * @return O novo nó criado.
     */
    // Alocação de memória para o novo nó.
    Node* no = malloc(sizeof(Node));

    // Definição das propriedades do novo nó: produto e quantidade conforme especificado, cor vermelha, e filhos são nós externos.
    strcpy(no->produto, produto);
    no->cor = RED; // New nodes are initially red
    no->esq = no->dir = EXTERNAL;
    no->qtd_produto = quantidade;

    // Retorna o novo nó.
    return no;
}

int isRed(Node* x) 
{
    /**
     * Esta função verifica se um nó é vermelho.
     *
     * @param x O nó a ser verificado.
     * @return 1 se o nó é vermelho, 0 caso contrário.
     */
    // Se o nó for NULL, retorna 0 (falso).
    if (x == NULL) return 0;

    // Retorna se a cor do nó é vermelha.
    return x->cor == RED;
}

Node* find_sucessor(Node* rbt)
{
    /**
     * Encontra o sucessor de um nó em uma árvore binária de busca rubro-negra.
     *
     * @param rbt O nó para encontrar o sucessor.
     * @return O nó sucessor ou o nó externo se não houver sucessor.
     */
    if (!rbt || rbt == EXTERNAL) return EXTERNAL; // Retorna o nó externo se o nó for nulo ou externo

    if (!rbt->esq || rbt->esq == EXTERNAL) return rbt; // Retorna o próprio nó se não houver filho à esquerda

    else return find_sucessor(rbt->esq); // Recursivamente encontra o sucessor na subárvore esquerda
}

Node* get_pai(Node** raiz, Node* no)
{
    /**
     * Obtém o nó pai de um nó específico em uma árvore binária de busca rubro-negra.
     *
     * @param raiz Um ponteiro para um ponteiro para o nó raiz da árvore.
     * @param no O nó para o qual se deseja obter o nó pai.
     * @return O nó pai do nó especificado ou o nó externo se não houver pai.
     */
    Node* pai = (*raiz); // Inicializa o nó pai com a raiz da árvore
    while (pai)
    {
        if (strcmp(pai->produto, no->produto) == 0)
            return EXTERNAL; // Retorna o nó externo se o nó atual for o nó especificado
        else if (pai->dir && strcmp(pai->dir->produto, no->produto) == 0)
            return pai; // Retorna o nó pai se o filho à direita for o nó especificado
        else if (pai->esq && strcmp(pai->esq->produto, no->produto) == 0)
            return pai; // Retorna o nó pai se o filho à esquerda for o nó especificado
        else if (strcmp(pai->produto, no->produto) > 0)
            pai = pai->esq; // Navega para a subárvore esquerda se o valor do nó pai for maior que o do nó especificado
        else
            pai = pai->dir; // Navega para a subárvore direita se o valor do nó pai for menor que o do nó especificado
    }
    
    return NULL; // Retorna NULL se o nó pai não for encontrado (nó especificado não está na árvore)
}

void transfere_pai(Node** raiz, Node* rbt, Node* target)
{   
    /**
     * Transfere um nó para substituir outro nó na árvore, atualizando os links do nó pai.
     *
     * @param raiz Um ponteiro para um ponteiro para o nó raiz da árvore.
     * @param rbt O nó que será substituído.
     * @param target O nó que será colocado no lugar de 'rbt'.
     */
    Node* paiRBT = get_pai(raiz, rbt); // Obtém o nó pai do nó 'rbt'

    if (paiRBT == EXTERNAL)
        (*raiz) = target; // Se o pai de 'rbt' for o nó externo, atualiza a raiz para apontar para 'target'
    else if (strcmp(paiRBT->esq->produto, rbt->produto) == 0)
        paiRBT->esq = target; // Se 'rbt' for o filho esquerdo de seu pai, atualiza o filho esquerdo para apontar para 'target'
    else
        paiRBT->dir = target; // Caso contrário, atualiza o filho direito para apontar para 'target'
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
    /**
     * Esta função insere um novo nó na árvore binária. O novo nó é criado com o produto e a quantidade especificados.
     *
     * @param h O nó atual na árvore.
     * @param produto O produto a ser inserido.
     * @param quantidade A quantidade do produto a ser inserida.
     * @return O nó atualizado.
     */

    // Se o nó atual é o nó externo (ou seja, o fim da árvore), a função cria um novo nó com o produto e a quantidade especificados e retorna.
    if (h == EXTERNAL) {
        return criar_no(produto, quantidade);
    }
    
    // A função então compara o produto com o produto no nó atual usando a função strcmp().
    int cmp = strcmp(produto, h->produto);
    
    if (cmp < 0) {
        h->esq = insert(h->esq, produto, quantidade);
    } else if (cmp > 0) {
        h->dir = insert(h->dir, produto, quantidade);
    }

    // A função retorna o nó atual.
    return h;
}

FPTA* returnFamilia(Node* raiz, char* produto) {
    /**
     * Esta função retorna uma estrutura FPTA (Filho, Pai, Tio, Avô) que contém os nós relevantes de um determinado produto na árvore.
     * Esta estrutura é útil ao executar operações de balanceamento em uma árvore Rubro-Negra.
     *
     * @param raiz O nó raiz da árvore.
     * @param produto O produto a ser buscado na árvore.
     * @return A estrutura FPTA para o produto especificado.
     */

    // A função começa inicializando uma nova estrutura FPTA com a raiz da árvore como o nó filho e todos os outros nós como NULL.
    FPTA* familia = malloc(sizeof(FPTA));
    familia->filho = raiz;
    familia->pai = NULL;
    familia->avo = NULL;
    familia->tio = NULL;

    // A função então entra em um laço while que continuará até que o nó filho seja NULL ou o produto do nó filho seja igual ao produto procurado.
    while (familia->filho && strcmp(produto, familia->filho->produto) != 0) {
        int cmp = strcmp(produto, familia->filho->produto);

        // Se o produto procurado é menor que o produto do nó filho, o código entra no bloco if cmp < 0.
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
            // O código então move para o filho esquerdo do nó atual para continuar a busca.
            familia->filho = familia->filho->esq;

        // Se o produto procurado é maior que o produto do nó filho, o código entra no bloco else if cmp > 0.
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
            // O código então move para o filho direito do nó atual para continuar a busca.
            familia->filho = familia->filho->dir;
        }
    }
    return familia;
}

int verificaSeExiste(Node* raiz, char* produto)
{
    /**
     * Esta função verifica se um produto específico existe na árvore.
     *
     * @param raiz O nó raiz da árvore.
     * @param produto O produto a ser verificado.
     * @return 1 se o produto existe na árvore, 0 caso contrário.
     */
    // Se a raiz da árvore é um nó externo, significa que a árvore está vazia, então retorna 0 (falso).
    if (raiz == EXTERNAL) return 0;

    // Compara o produto passado como parâmetro com o produto no nó raiz atual. 
    // Retorna um número negativo se o produto for menor do que raiz->produto, zero se forem iguais e um número positivo se for maior.
    int tam = strcmp(produto, raiz->produto);

    // Enquanto o nó raiz não for um nó externo (ou seja, até que todos os nós da árvore tenham sido verificados).
    while(raiz != EXTERNAL) { 
        // Faz a comparação novamente, pois o nó raiz pode ter sido atualizado.
        tam = strcmp(produto, raiz->produto);

        // Se a comparação retornar 0 (os produtos são iguais), retorna 1 (verdadeiro).
        if (tam == 0)
        {
            return 1;
        }
        // Se a comparação retornar um número positivo (o produto é maior do que raiz->produto), move para o filho à direita.
        else if (tam > 0)
        {
            raiz = raiz->dir;
        }
        // Se a comparação retornar um número negativo (o produto é menor do que raiz->produto), move para o filho à esquerda.
        else if (tam < 0)
        {
            raiz = raiz->esq;
        }
    }

    // Se o produto não for encontrado após verificar todos os nós, retorna 0 (falso).
    return 0;
}


Node* insertRoot(Node* root, char* produto, int quantidade) {
    /**
     * Esta função insere um novo nó, com um determinado produto e quantidade, na raiz de uma árvore Rubro-Negra.
     * A árvore é auto-balanceada após a inserção para preservar as propriedades da árvore Rubro-Negra.
     *
     * @param root O nó raiz da árvore.
     * @param produto O produto a ser inserido.
     * @param quantidade A quantidade do produto.
     * @return A raiz da árvore após a inserção e o auto-balanceamento.
     */

    // Primeiro, a função verifica se o produto já existe na árvore.
    int existe = verificaSeExiste(root, produto);

    // Se o produto já existe, imprime uma mensagem de erro e retorna a raiz da árvore sem alterações.
    if (existe == 1) {
        printf("\nProduto ja existente, adicione outro\n");
        return root;
    }
    
    // Se o produto não existe, ele é inserido na árvore.
    root = insert(root, produto, quantidade);

    // A função returnFamilia() é chamada para obter a estrutura da família do nó inserido, que inclui o nó pai, avô e tio.
    FPTA* familia = returnFamilia(root, produto);
    if (familia->avo != NULL) {
        FPTA* familia_old = returnFamilia(root, familia->pai->produto);
    }

    // Variáveis auxiliares para ajudar no balanceamento da árvore.
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

        // Caso o tio for negro ou null
        } else {
            // Rotacao a esquerda CASO 2, pai a esquerda do avo, filho a direita do pai e ambos vermelhos
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

            // Rotacao a direita CASO 2, pai a direita do avo, filho a esquerda do pai e ambos vermelhos
            } else if ((familia->avo->dir == familia->pai) && (familia->filho == familia->pai->esq) && 
                (familia->filho->cor == RED) && (familia->pai->cor == RED)) {
                familia->pai->esq = familia->filho->dir;
                familia->filho->dir = familia->pai;
                familia->avo->dir = familia->filho;
                familia = returnFamilia(root, familia->pai->produto);
                familia->avo->dir = familia->pai->esq;
                familia->pai->esq = familia->avo;
                // Troca as cores
                familia->pai->cor = BLACK;
                familia->avo->cor = RED;
                if (root == familia->avo) {
                    root = familia->pai;
                }
                // Define o pai como novo filho para ir ate a raiz
                familia = returnFamilia(root, familia->pai->produto);

            // Rotacao a direita CASO 1, pai a esquerda do avo e filho a esquerda do pai
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
                // Troca as cores
                familia->pai->cor = BLACK;
                familia->avo->cor = RED;
                if (root == familia->avo) {
                    root = familia->pai;
                }
                // Define o pai como novo filho para ir ate a raiz
                familia = returnFamilia(root, familia->pai->produto);

            // Rotacao a esquerda CASO 1, pai a direita do avo e filho a direita do pai
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
                // Troca as cores
                familia->pai->cor = BLACK;
                familia->avo->cor = RED;
                if (root == familia->avo) {
                    root = familia->pai;
                }
                // Define o pai como novo filho para ir ate a raiz
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