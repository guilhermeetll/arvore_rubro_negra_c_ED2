#include "stdio.h"
#include "tree.h"

int main(){
    int resp;
    printf("***************************************************\n");
    printf("| 1- Cadastrar produto                            |\n");
    printf("| 2- Excluir produto                              |\n");
    printf("| 3- Atualizar a quantidade do produto no estoque |\n");
    printf("| 4- Listar os produtos cadastrados               |\n");
    printf("| 5- Listar os  produtos em estoque               |\n");
    printf("| 6- Imprimir a arvore                            |\n");
    printf("| 7- Sair                                         |\n");
    printf("***************************************************\n");
    do{
        printf(">> ");
        scanf("%d", &resp);
        switch (resp)
        {
        case 1:
            printf("1\n");
            break;
        case 2:
            printf("2\n");
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
