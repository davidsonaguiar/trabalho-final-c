#include <stdio.h>
#include "./menus.h"

void menuPrincipal() {

    int opcao;

    do {
        printf("\n+----------------------------+\n");
        printf("| ===== MENU PRINCIPAL ===== |\n");
        printf("+----------------------------+\n");

        printf("1 - Menu do Aluno\n");
        printf("2 - Menu do Professor\n");
        printf("3 - Menu da Turma\n");
        printf("0 - Sair\n");

        printf("Escolha uma das opcoes acima: ");
        scanf("%d", &opcao);

        printf("\n");

        switch (opcao) {
            case 1:
                menuAluno();
                break;
            
            case 2:
                menuProfessor();
                break;
            
            case 3:
                menuTurma();
                break;
            
            case 0:
                printf("Saindo...\n");
                return;
                break;
            
            default:
                printf("Opcao Invalida!\n");
                break;
        }
    } while(1);
}