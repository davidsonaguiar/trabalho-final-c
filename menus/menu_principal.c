#include <stdio.h> // Inclui a biblioteca de entrada/saída padrão
#include "./menus.h" // Inclui o arquivo de cabeçalho 'menus.h'
// Sistema de para o menu principal.
void menuPrincipal() {

    int opcao;

    do {
        printf("\n+----------------------------+\n");
        printf("| ===== MENU PRINCIPAL ===== |\n");
        printf("+----------------------------+\n");
// Menssagens do menu principal.
        printf("1 - Menu do Aluno\n");
        printf("2 - Menu do Professor\n");
        printf("3 - Menu da Turma\n");
        printf("0 - Sair\n");
// Solicitando escolha.
        printf("Escolha uma das opcoes acima: ");
        scanf("%d", &opcao);

        printf("\n");

        switch (opcao) {
            case 1:
                menuAluno(); // Chamando menu aluno.
                break;
            
            case 2:
                menuProfessor(); // Chamando menu professor.
                break;
            
            case 3:
                menuTurma(); // Chamando menu turma.
                break;
            
            case 0:
                printf("Saindo...\n"); // função para sair e apresentar menssagem.
                return;
                break;
            
            default:
                printf("Opcao Invalida!\n"); // Casso nenhuma das opções seja escolhida.
                break;
        }
    } while(1); //loop para manter o menu em execução.
}