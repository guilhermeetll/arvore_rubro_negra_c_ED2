#include "stdio.h"
#include "stdlib.h"
#include "tree.h"
#include <string.h>

void menu(){
    printf("\n***************************************************\n");
    printf("| 1- Cadastrar produto                            |\n");
    printf("| 2- Excluir produto                              |\n");
    printf("| 3- Atualizar a quantidade do produto no estoque |\n");
    printf("| 4- Listar os produtos cadastrados               |\n");
    printf("| 5- Listar os  produtos em estoque               |\n");
    printf("| 6- Imprimir a arvore                            |\n");
    printf("| 7- Sair                                         |\n");
    printf("***************************************************\n");
}

int main()
{
    Node* raiz = NULL;
    int resp, quantidade;
    char nome[100];
    do
    {   menu();
        printf(">> ");
        scanf("%d", &resp);
        switch (resp)
        {
        case 1:
            printf("Digite o nome do produto >> ");
            scanf("%s", nome);
            printf("Digite a quantidade >> ");
            scanf("%d", &quantidade);
            raiz = insertRoot(raiz, nome, quantidade);
            break;
        case 2:
            break;
        case 3:
            char produto[200];
            int qtd_produto;
            fflush(stdin);
            printf("Informe o produto que deseja atualizar >> ");
            scanf("%s", produto);
                Node* no = malloc(sizeof(Node));
                no = busca(raiz, produto);
                if (no == NULL){
                    printf("Registro não encontrado\n");
                    break;
                }
                else {
                    printf("Informe a nova quantidade >> ");
                    scanf("%d", &qtd_produto);
                    no->qtd_produto = qtd_produto;
                    printf("*****************\n");
                    printf("|Produto: %s\n", no->produto);
                    printf("|Nova Quantidade: %d \n", no->qtd_produto);
                    printf("*****************\n");
                    break;
                }
            break;

        case 4:
            printf("Produtos: ");
            printTreeHelper(raiz);
            break;

        case 5:
            printf("Produtos em estoque: ");
            printEstoque(raiz);
            break;
            
        case 6:
            imprime(raiz, 1);   
            break;
        case 7:
            printf("Exit...\n");
            break;
        default:
            break;
        }
    }while (resp != 7);
    return 0;
}
