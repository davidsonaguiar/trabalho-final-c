#include <stdio.h>
#include "./menus.h"

void menuAluno() {

    int opcao;

    do {
        printf("\n+------------------------+\n");
        printf("| ===== MENU ALUNO ===== |\n");
        printf("+------------------------+\n");

        printf("1 - Cadastrar Aluno\n");
        printf("2 - Mostrar Alunos\n");
        printf("3 - Atualizar Aluno\n");
        printf("4 - Remover Aluno\n");
        printf("0 - Menu Principal\n\n");

        printf("Escolha uma das opcoes acima: ");
        scanf("%d", &opcao);

        printf("\n");

        switch (opcao) {
            case 1:
                printf("em desenvolvimento");
                break;
            
            case 2:
                printf("em desenvolvimento");
                break;
            
            case 3:
                printf("em desenvolvimento");
                break;
            
            case 4:
                printf("em desenvolvimento");
                break;
            
            case 0:
                return;
                break;
            
            default:
                break;
            }
    } while(1);
}