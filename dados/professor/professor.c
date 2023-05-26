#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./professor.h" // Importando o cabeçalho do professor, com sua fuções, tipos e constantes. 


void cadastrarProfessor() {
    Professor professor;
    FILE* arquivo;

    printf("--- CADASTRO DE PROFESSOR ---\n");

    // recebebendo a matricula.
    printf("Matrícula: ");
    scanf("%s", professor.matricula);

    // recebendo o cpf.
    printf("CPF: ");
    scanf("%s", professor.cpf);

    // Verifica se o professor já está cadastrado
    arquivo = fopen("dados/professor/professores.bin", "rb");
    if (arquivo != NULL) {
        Professor professorExistente;
        while (fread(&professorExistente, sizeof(Professor), 1, arquivo)) {
            if (strcmp(professorExistente.matricula, professor.matricula) == 0 || strcmp(professorExistente.cpf, professor.cpf) == 0) {
                printf("Professor já cadastrado!\n");
                fclose(arquivo);
                return;
            }
        }
        fclose(arquivo);
    }

    
    printf("Nome: ");
    scanf(" %[^\n]", professor.nome);
    printf("Endereço:\n");
    printf("Logradouro: ");
    scanf(" %[^\n]", professor.endereco.logradouro);
    printf("Bairro: ");
    scanf(" %[^\n]", professor.endereco.bairro);
    printf("Cidade: ");
    scanf(" %[^\n]", professor.endereco.cidade);
    printf("Estado: ");
    scanf(" %[^\n]", professor.endereco.estado);
    printf("Número: ");
    scanf(" %[^\n]", professor.endereco.numero);

    arquivo = fopen("dados/professor/professores.bin", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fwrite(&professor, sizeof(Professor), 1, arquivo);
    fclose(arquivo);

    printf("Professor cadastrado com sucesso!\n");
}



void imprimirProfessores() {
    Professor professor;
    FILE* arquivo = fopen("dados/professor/professores.bin", "rb");

    printf("--- PROFESSORES CADASTRADOS ---\n");

    if (arquivo == NULL) {    
        printf("Não há professores cadastrados!\n");
        return;
    }

    if(fread(&professor, sizeof(Professor), 1, arquivo) == 0) {
        printf("Não há alunos cadastrados!\n");
    } else {
        while (fread(&professor, sizeof(Professor), 1, arquivo)) {
            printf("Matrícula: %s\n", professor.matricula); 
            printf("CPF: %s\n", professor.cpf); 
            printf("Nome: %s\n", professor.nome);
            printf("Endereço:\n");
            printf("Logradouro: %s\n", professor.endereco.logradouro);
            printf("Bairro: %s\n", professor.endereco.bairro);
            printf("Cidade: %s\n", professor.endereco.cidade);
            printf("Estado: %s\n", professor.endereco.estado);
            printf("Número: %s\n", professor.endereco.numero);
            printf("------------\n");
        }
    }

    fclose(arquivo);
}



void atualizarProfessor() {
    char matricula[10];
    Professor professor;
    FILE* arquivo;
    long int posicao;

    printf("--- ATUALIZAÇÃO DE PROFESSOR ---\n");
    printf("Matrícula do professor a ser atualizado: ");
    scanf("%s", matricula);

    arquivo = fopen("dados/professor/professores.bin", "r+b");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    while (fread(&professor, sizeof(Professor), 1, arquivo)) {
        if (strcmp(professor.matricula, matricula) == 0) {
            posicao = ftell(arquivo) - sizeof(Professor);
            fseek(arquivo, posicao, SEEK_SET);

            printf("CPF: ");
            scanf("%s", professor.cpf);
            printf("Nome: ");
            scanf(" %[^\n]", professor.nome);
            printf("Endereço:\n");
            printf("Logradouro: ");
            scanf(" %[^\n]", professor.endereco.logradouro);
            printf("Bairro: ");
            scanf(" %[^\n]", professor.endereco.bairro);
            printf("Cidade: ");
            scanf(" %[^\n]", professor.endereco.cidade);
            printf("Estado: ");
            scanf(" %[^\n]", professor.endereco.estado);
            printf("Número: ");
            scanf(" %[^\n]", professor.endereco.numero);

            fwrite(&professor, sizeof(Professor), 1, arquivo);
            fclose(arquivo);

            printf("Professor atualizado com sucesso!\n");
            return;
        }
    }

    fclose(arquivo);
    printf("Professor não encontrado!\n");
}



void descadastrarProfessor() {
    char matricula[10];
    Professor professor;
    FILE* arquivo;
    FILE* arquivoTurmas;
    int professorEncontrado = 0;

    printf("--- DESCADASTRAR PROFESSOR ---\n");
    printf("Matrícula do professor a ser descadastrado: ");
    scanf("%s", matricula);

    // Verifica se o professor está associado a alguma turma
    arquivoTurmas = fopen("dados/turma/turmas.bin", "rb");
    if (arquivoTurmas != NULL) {
        Turma turma;
        while (fread(&turma, sizeof(Turma), 1, arquivoTurmas)) {
            if (strcmp(turma.professor.matricula, matricula) == 0) {
                printf("O professor está associado à turma %s. Não é possível descadastrá-lo!\n", turma.codigo);
                fclose(arquivoTurmas);
                return;
            }
        }
        fclose(arquivoTurmas);
    }

    arquivo = fopen("dados/professor/professores.bin", "r+b");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    FILE* arquivoTemporario = fopen("dados/professor/professores_temp.bin", "w+b");
    if (arquivoTemporario == NULL) {
        printf("Erro ao abrir o arquivo temporário!\n");
        fclose(arquivo);
        return;
    }

    while (fread(&professor, sizeof(Professor), 1, arquivo)) {
        if (strcmp(professor.matricula, matricula) == 0) {
            professorEncontrado = 1;
        } else {
            fwrite(&professor, sizeof(Professor), 1, arquivoTemporario);
        }
    }

    fclose(arquivo);
    fclose(arquivoTemporario);

    if (professorEncontrado) {
        remove("dados/professor/professores.bin");
        rename("dados/professor/professores_temp.bin", "dados/professor/professores.bin");
        printf("Professor descadastrado com sucesso!\n");
    } else {
        remove("dados/professor/professores_temp.bin");
        printf("Professor não encontrado!\n");
    }
}



void imprimirProfessoresSemTurma() {

    FILE* arquivoTurmas = fopen("dados/turma/turmas.bin", "rb");
    FILE* arquivoProfessores = fopen("dados/professor/professores.bin", "rb");

    if (arquivoTurmas == NULL) {
        printf("Não há turmas cadastradas!\n");
        return;
    }

    if (arquivoProfessores == NULL) {
        printf("Não há professores cadastrados!\n");
        fclose(arquivoTurmas);
        return;
    }

    Turma turma;
    Professor professor;
    int professorAssociado;

    printf("--- PROFESSORES SEM TURMA ---\n");

    while (fread(&professor, sizeof(Professor), 1, arquivoProfessores)) {
        fseek(arquivoTurmas, 0, SEEK_SET);
        professorAssociado = 0;

        while (fread(&turma, sizeof(Turma), 1, arquivoTurmas)) {
            if (strcmp(professor.matricula, turma.professor.matricula) == 0) {
                professorAssociado = 1;
                break;
            }
        }

        if (!professorAssociado) {
            printf("Matrícula: %s\n", professor.matricula);
            printf("Matrícula: %s\n", professor.nome);
            printf("Matrícula: %s\n", professor.cpf);
        }
    }

    fclose(arquivoTurmas);
    fclose(arquivoProfessores);
}