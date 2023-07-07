#include "stdio.h"
#include "stdlib.h"
#include "tree.h"
#include "string.h"

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
    EXTERNAL = createEXTERNAL();
    Node* raiz = EXTERNAL;
    char produto[200];
    int resp;
    insert_no(&raiz, "33");
    insert_no(&raiz, "47");
    insert_no(&raiz, "15");    
    insert_no(&raiz, "11");
    insert_no(&raiz, "20");
    insert_no(&raiz, "38");
    insert_no(&raiz, "51");
    insert_no(&raiz, "18");
    insert_no(&raiz, "49");
    insert_no(&raiz, "60");
    insert_no(&raiz, "10");

    raiz->esq->esq->cor = BLACK;
    raiz->esq->dir->cor = BLACK;
    raiz->dir->dir->cor = BLACK;
    raiz->dir->esq->cor = BLACK;
    raiz->cor = BLACK;
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
            break;
        case 2:
            char t[2];
            printf(">> ");
            fflush(stdin);
            scanf("%s", t);
            Node* node = busca(raiz, t);
            Node* percorre = raiz;
            Node* pai = NULL;
            while (True)
            {
                
                if (raiz == NULL) break;
                if (strcmp(percorre->produto, node->produto) == 0)
                {   
                    remocao(&raiz, node);
                    break;
                }
                else if (strcmp(percorre->produto, node->produto) > 0)
                {
                    pai = percorre;
                    percorre = percorre->esq;
                }
                else if (strcmp(percorre->produto, node->produto) < 0) 
                {
                    pai = percorre;
                    percorre = percorre->dir;
                }
                else break;
            }
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
        case 4:
            lista_produtos(raiz, resp);
            break;
        case 5:
            lista_produtos(raiz, resp);
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
