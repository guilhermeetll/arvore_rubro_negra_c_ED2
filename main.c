#include <stdio.h>
#include <stdlib.h>

// Definição das cores
#define RED 0
#define BLACK 1

// Definição da estrutura do nó
typedef struct Node {
    int data;
    int color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

// Função auxiliar para criar um novo nó
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

// Função auxiliar para trocar os nós
void swapNodes(Node** root, Node* x, Node* y) {
    Node* parent_x = x->parent;
    Node* parent_y = y->parent;

    if (parent_x == NULL)
        *root = y;
    else if (x == parent_x->left)
        parent_x->left = y;
    else
        parent_x->right = y;

    if (parent_y != NULL)
        y->parent = parent_x;

    x->parent = y;
    y->parent = parent_x;
}

// Função auxiliar para realizar uma rotação à esquerda
void leftRotate(Node** root, Node* x) {
    Node* y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Função auxiliar para realizar uma rotação à direita
void rightRotate(Node** root, Node* x) {
    Node* y = x->left;
    x->left = y->right;

    if (y->right != NULL)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->right = x;
    x->parent = y;
}

// Função auxiliar para corrigir a árvore após a inserção de um nó
void fixInsertion(Node** root, Node* node) {
    while (node != *root && node->parent->color == RED) {
        Node* parent = node->parent;
        Node* grandparent = parent->parent;

        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;

            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    node = parent;
                    leftRotate(root, node);
                }

                parent = node->parent;
                grandparent = parent->parent;
                parent->color = BLACK;
                grandparent->color = RED;
                rightRotate(root, grandparent);
            }
        } else {
            Node* uncle = grandparent->left;

            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    node = parent;
                    rightRotate(root, node);
                }

                parent = node->parent;
                grandparent = parent->parent;
                parent->color = BLACK;
                grandparent->color = RED;
                leftRotate(root, grandparent);
            }
        }
    }

    (*root)->color = BLACK;
}

// Função para inserir um nó na árvore rubro-negra
void insertNode(Node** root, int data) {
    Node* newNode = createNode(data);
    Node* parent = NULL;
    Node* current = *root;

    while (current != NULL) {
        parent = current;

        if (data < current->data)
            current = current->left;
        else if (data > current->data)
            current = current->right;
        else {
            printf("O nó com valor %d já existe na árvore.\n", data);
            free(newNode);
            return;
        }
    }

    newNode->parent = parent;

    if (parent == NULL)
        *root = newNode;
    else if (data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    fixInsertion(root, newNode);
}

// Função auxiliar para imprimir a árvore em ordem
void inOrderTraversal(Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->data);
        inOrderTraversal(root->right);
    }
}

// Função principal
int main() {
    Node* root = NULL;

    insertNode(&root, 7);
    insertNode(&root, 3);
    insertNode(&root, 18);
    insertNode(&root, 10);
    insertNode(&root, 22);
    insertNode(&root, 8);
    insertNode(&root, 11);
    insertNode(&root, 26);
    insertNode(&root, 2);

    printf("Árvore em ordem: ");
    inOrderTraversal(root);
    printf("\n");

    return 0;
}