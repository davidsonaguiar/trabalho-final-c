#include <stdio.h>       // Inclui a biblioteca de entrada/saída padrão
#include "./menus.h"     // Inclui o arquivo de cabeçalho 'menus.h'

void menuAluno() {
    int opcao;

    do {
        printf("\n+------------------------+\n");
        printf("| ===== MENU ALUNO ===== |\n");
        printf("+------------------------+\n");

        printf("1 - Cadastrar Aluno\n");    // Opção para cadastrar um aluno
        printf("2 - Mostrar Alunos\n");     // Opção para mostrar os alunos cadastrados
        printf("3 - Atualizar Aluno\n");    // Opção para atualizar os dados de um aluno
        printf("4 - Remover Aluno\n");      // Opção para remover um aluno
        printf("5 - Mostrar Aluno\n");      // Opção para remover um aluno
        printf("0 - Menu Principal\n\n");  // Opção para retornar ao menu principal

        printf("Escolha uma das opcoes acima: ");   // Solicita ao usuário que escolha uma opção
        scanf("%d", &opcao);                        // Lê a opção escolhida pelo usuário

        printf("\n");

        switch (opcao) {
            case 1:
                cadastrarAluno();    // Chama a função para cadastrar um aluno
                break;
            
            case 2:
                imprimirAlunos();    // Chama a função para imprimir os alunos cadastrados
                break;
            
            case 3:
                atualizarAluno();    // Chama a função para atualizar os dados de um aluno
                break;
            
            case 4:
                descadastrarAluno(); // Chama a função para remover um aluno
                break;

            case 5:
                imprimirAluno(); // Chama a função para imprimir um aluno especifico
                break;
            
            case 0:
                return;              // Retorna ao menu principal
                break;
            
            default:
                break;
        }
    } while(1);  // Loop infinito para manter o menu em execução
}
