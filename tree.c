#include "stdio.h"
#include "stdlib.h"
#include "tree.h"
#include "string.h"


Node* criar_no(char* produto, int quantidade)
{
    Node* no = malloc(sizeof(Node));
    no->cor = RED;
    no->esq = NULL;
    no->dir = NULL;
    strcpy(no->produto, produto);
    no->qtd_produto = quantidade;
    return no;
}

Node* createNode(char* produto, Cor color) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    strcpy(newNode->produto, produto);
    newNode->qtd_produto = 100;
    newNode->esq = NULL;
    newNode->dir = NULL;
    newNode->cor = color;

    return newNode;
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
        return createNode(produto, BLACK);

    // Inserção do nó seguindo as regras da árvore Red-Black
    int tam = strcmp(produto, raiz->produto);
    printf("\n%d\n", tam);
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

void printSpaces(int count) {
    for (int i = 0; i < count; i++) {
        printf(" ");
    }
}

void printTreeHelper(Node* root, int space) {
    if (root == NULL)
        return;

    space += 5;

    printTreeHelper(root->dir, space);

    printf("\n");
    printSpaces(space);
    printf("%s", root->produto);
    if (root->cor == RED)
        printf(" (R)\n");
    else
        printf(" (B)\n");

    printTreeHelper(root->esq, space);
}

void printTree(Node* root) {
    printTreeHelper(root, 0);
}