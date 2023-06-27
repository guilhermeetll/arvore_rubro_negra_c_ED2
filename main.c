#include "stdio.h"
#include "stdlib.h"
#include "tree.h"

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
    //raiz->esq = criar_no("teste2");
    //raiz->dir = criar_no("teste5");
    //raiz->dir->dir = criar_no("teste6");
    int resp, quantidade;
    char nome[100];
    do
    {   menu();
        printf(">> ");
        scanf("%d", &resp);
        switch (resp)
        {
        case 1:
            printf("Digite o nome do produto: ");
            scanf("%s", nome);
            printf("Digite a quantidade: ");
            scanf("%d", &quantidade);
            raiz = insertRoot(raiz, nome);
            printf("\nRaiz = %s", raiz->produto);
            break;
        case 2:
            printf("2\n");
            break;
        case 3:
            char produto[200];
            int qtd_produto;
            fflush(stdin);
            printf("Informe o produto e a quantidade que deseja atualizar: \n>> ");
            scanf("%s%d", produto,&qtd_produto);
                Node* no = malloc(sizeof(Node));
                no = busca(raiz, produto);
                if (no == NULL){
                    printf("Registro não encontrado\n");
                    break;
                }
                else {
                    no->qtd_produto = qtd_produto;
                    printf("*****************\n");
                    printf("|produto: %s\n", no->produto);
                    printf("|quantidade: %d \n", no->qtd_produto);
                    printf("*****************\n");
                    break;
                }
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
