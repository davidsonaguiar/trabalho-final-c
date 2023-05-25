#include <stdio.h>
#include "./menus/menus.h"

int main(int argc, char const *argv[])
{

    int opcao;

    do {
        printf("==== Menu principal ====\n\n");
        printf("1 - Menu do aluno\n");
        printf("2 - Menu do professor\n");
        printf("0 - Sair\n");

        printf("Escolha uma das opcoes acima: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            menu_aluno();
            break;

        case 2:
            menu_professor();
            break;
            
        case 0:
            printf("Finalizando app...\n\n");
            return 0;
            break;
        
        default:
            printf("Opcao inválida!! Tente novamente\n\n");
            break;
        }
        
    } while(1);
}
