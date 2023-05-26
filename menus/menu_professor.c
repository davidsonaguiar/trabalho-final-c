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

        printf("Escolha uma das opcoes acima:");
        scanf("%d", &opcao);
        
        printf("\n");

        

        printf("\n");

        switch (opcao) {
            case 1:
                cadastrarProfessor();
                break;
            
            case 2:
                imprimirProfessores();
                break;
            
            case 3:
                imprimirProfessoresSemTurma();
                break;
            
            case 4:
                atualizarProfessor();
                break;
            
            case 5:
                descadastrarProfessor();
                break;
            
            case 0:
                return;
                break;
            
            default:
                break;
        }
    } while(1);
}