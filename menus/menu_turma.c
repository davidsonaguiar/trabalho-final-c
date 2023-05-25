#include <stdio.h>
#include "./menus.h"

void menuTurma() {

    int opcao;

    do {
        printf("\n+------------------------+\n");
        printf("| ===== MENU TURMA ===== |\n");
        printf("+------------------------+\n");

        printf("1 - Cadastrar Turma\n");
        printf("2 - Mostrar Turmas\n");
        printf("3 - Atualizar Turma\n");
        printf("4 - Remover Turma\n");
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