/**
 * Grupo 7
 * Gabriela júlia Tavares Elias
 * Guilherme Travaglia Largura
 * Lucas Ferreira de Souza Santos
*/

// Bibliotecas necessárias para o funcionamento do programa
#include "stdio.h"
#include "stdlib.h"
#include "tree.h"
#include "string.h"



// Função que exibe o menu principal para o usuário
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

// Função principal onde todo o programa é executado
int main()
{
    // Inicializando a árvore rubro-negra
    EXTERNAL = createEXTERNAL();
    Node* raiz = EXTERNAL;

    // Variáveis para armazenar a resposta do usuário, quantidade e nome do produto
    char produto[200];
    int resp, quantidade;
    char nome[100];

    // Loop principal que executa as operações do menu até que o usuário escolha "Sair"
    do
    {   
        // Exibindo o menu e lendo a escolha do usuário
        menu();
        printf(">> ");
        scanf("%d", &resp);

        // O switch case executa a operação com base na escolha do usuário
        switch (resp)
        {
        case 1: // Cadastrando um novo produto
            printf("Digite o nome do produto >> ");
            scanf("%s", nome);
            printf("Digite a quantidade >> ");
            scanf("%d", &quantidade);
            raiz = insertRoot(raiz, nome, quantidade); // Inserindo o produto na árvore
            break;
        case 2: // Excluindo um produto existente
            char t[2];
            printf("Informe o produto que deseja remover: ");
            fflush(stdin);
            scanf("%s", t);
            Node* node = busca(raiz, t); // Buscando o produto na árvore

            if (!node) // Se o produto não existir, o usuário é informado
            {
                printf("O produto não existe!\n");
                break;
            }
            // Caso contrário, o produto é removido
            Node* percorre = raiz;
            Node* pai = NULL;
            while (True)
            {
                // O código a seguir realiza a busca pelo produto a ser removido
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
        case 3: // Atualizando a quantidade de um produto existente
            int qtd_produto;
            fflush(stdin);
            printf("Informe o produto e a quantidade que deseja atualizar: \n>> ");
            scanf("%s%d", produto,&qtd_produto);
                Node* no = malloc(sizeof(Node));
                no = busca(raiz, produto); // Buscando o produto na árvore

                // Se o produto não existir, o usuário é informado
                if (no == NULL){
                    printf("Registro não encontrado\n");
                    break;
                }
                else { // Caso contrário, a quantidade é atualizada
                    no->qtd_produto = qtd_produto;
                    printf("*****************\n");
                    printf("|produto: %s\n", no->produto);
                    printf("|quantidade: %d \n", no->qtd_produto);
                    printf("*****************\n");
                    break;
                }
            break;
        case 4: // Listando todos os produtos cadastrados
            printf("Produtos: ");
            printTreeHelper(raiz); // Imprimindo a lista
            break;
        case 5: // Listando todos os produtos em estoque
            printf("Produtos em estoque: ");
            printEstoque(raiz); // Imprimindo os produtos em estoque
            break;
        case 6: // Imprimindo a árvore
            imprime(raiz, 1);   
            break;
        case 7: // Saindo do programa
            printf("Exit...\n");
            break;
        default: // Caso uma opção inválida seja selecionada, nada acontece
            break;
        }
    }while (resp != 7); // Fim do loop do menu principal
    return 0; // Terminando a execução do programa
}