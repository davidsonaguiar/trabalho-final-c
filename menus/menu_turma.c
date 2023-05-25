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
                cadastrarTurma();
                break;
            
            case 2:
                imprimirTurmas();
                break;
            
            case 3:
                atualizarProfessor();
                break;
            
            case 4:
                descadastrarTurma();
                break;
            
            case 0:
                return;
                break;
            
            default:
                break;
            }
    } while(1);
}