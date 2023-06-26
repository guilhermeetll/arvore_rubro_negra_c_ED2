#include "stdio.h"
#include "stdlib.h"
#include "tree.h"

void menu(){
    printf("***************************************************\n");
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
    char produto[200];
    int resp;
    do
    {   menu();
        printf(">> ");
        scanf("%d", &resp);
        switch (resp)
        {
        case 1:
            // printf("Informe o produto que deseja cadastrar: \n>> ");
            // scanf("%s", produto);
            // insert_no(&raiz, produto);
            insert_no(&raiz, "b");
            insert_no(&raiz, "c");
            insert_no(&raiz, "z");
            insert_no(&raiz, "a");
            raiz->cor = BLACK;
            break;
        case 2:
            printf("2\n");
            break;
        case 3:
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
