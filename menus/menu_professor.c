#include <stdio.h>
#include "./menus.h"

void menuProfessor() {

    int opcao;

    do {
        printf("\n+----------------------------+\n");
        printf("| ===== MENU PROFESSOR ===== |\n");
        printf("+----------------------------+\n");

        printf("1 - Cadastrar Professor\n");
        printf("2 - Mostrar Professores\n");
        printf("3 - Mostrar Professores sem Turma\n");
        printf("4 - Atualizar Professor\n");
        printf("5 - Remover Professor\n");
        printf("0 - Menu Principal\n\n");

        printf("Escolha uma das opcoes acima: ");

        printf("\n");

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
            
            case 5:
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