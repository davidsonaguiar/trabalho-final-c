#include <stdio.h> // Inclui a biblioteca de entrada/saída padrão
#include "./menus.h"   // Inclui o arquivo de cabeçalho 'menus.h'
// sistema de menu para turma.
void menuTurma() {

    int opcao;

    do {
        printf("\n+------------------------+\n");
        printf("| ===== MENU TURMA ===== |\n");
        printf("+------------------------+\n");
// Menssagem do menu para turma.
        printf("1 - Cadastrar Turma\n");
        printf("2 - Mostrar Turmas\n");
        printf("3 - Atualizar Turma\n");
        printf("4 - Remover Turma\n");
        printf("5 - Adicionar Aluno\n");
        printf("6 - Remover Aluno da Turma\n");
        printf("7 - Cadastrar Professor\n");
        printf("8 - Descadastrar Professor\n");
        printf("9 - Mostrar media das turmas\n");
        printf("0 - Menu Principal\n\n");
// Solicitando ao usário que escolha uma das opções
        printf("Escolha uma das opcoes acima: ");
        scanf("%d", &opcao);

        printf("\n");

        switch (opcao) {
            case 1:
                cadastrarTurma(); // Chamando a função cadastrar turma.
                break;
            
            case 2:
                imprimirTurmas(); // Chamando a função imrpimir turma.
                break;
            
            case 3:
                atualizarTurma(); // Chamando a função atualizar.
                break;
            
            case 4:
                descadastrarTurma(); // Chamando a função descadastrar turma.
                break;
            
            case 5:
                adicionarAluno(); // Chamando a função adcionar aluno.
                break;
            
            case 6:
                descadastrarAlunoTurma(); // Chamando a função descastrar aluno
                break;

            case 7:
                cadastrarProfessorTurma();
                break;
                
            case 8:
                descadastrarProfessorTurma();
                break;
            
            case 9:
                imprimirMedia(); // Chamando a função imprimir média
                break;

            case 0:
                return;
                break;
            
            default:
                break;
            }
    } while(1); //loop para manter o menu em execução
}