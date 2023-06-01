#include <stdio.h> // Inclui a biblioteca de entrada/saída padrão
#include "./menus.h"  // Inclui o arquivo de cabeçalho 'menus.h'
// Sistema para menu de professores.
void menuProfessor() {

    int opcao;

    do {
        printf("\n+----------------------------+\n");
        printf("| ===== MENU PROFESSOR ===== |\n");
        printf("+----------------------------+\n");
// Menssagem do menu dos professores.
        printf("1 - Cadastrar Professor\n");
        printf("2 - Mostrar Professores\n");
        printf("3 - Mostrar Professores sem Turma\n");
        printf("4 - Atualizar Professor\n");
        printf("5 - Remover Professor\n");
        printf("0 - Menu Principal\n\n");
// Solicitando ao usário que escolha uma das opções.
        printf("Escolha uma das opcoes acima:");
        scanf("%d", &opcao);
        
        printf("\n");

        

        printf("\n");

        switch (opcao) {
            case 1:
                cadastrarProfessor(); // chamando função de cadastrar professores.
                break;
            
            case 2:
                imprimirProfessores(); // chamanda função de imprimir professores cadastrados.
                break;
            
            case 3:
                imprimirProfessoresSemTurma(); // Chamando função de imprimir professores sem turma
                break;
            
            case 4:
                atualizarProfessor(); // Chamando função de atualizar professores.
                break;
            
            case 5:
                descadastrarProfessor(); // Chamando função de descadastro de professores.
                break;
            
            case 0:
                return;
                break;
            
            default:
                break;
        }
    } while(1); //loop para manter o menu em execução.
}