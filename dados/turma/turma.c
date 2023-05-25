#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./turma.h"

void cadastrarTurma() {
    Turma turma;
    FILE* arquivo;

    printf("--- CADASTRO DE TURMA ---\n");
    printf("Código: ");
    scanf("%s", turma.codigo);

    // Verifica se a turma já está cadastrada
    arquivo = fopen("dados/turma/turmas.bin", "rb");
    if (arquivo != NULL) {
        Turma turmaExistente;
        while (fread(&turmaExistente, sizeof(Turma), 1, arquivo)) {
            if (strcmp(turmaExistente.codigo, turma.codigo) == 0) {
                printf("Turma já cadastrada!\n");
                fclose(arquivo);
                return;
            }
        }
        fclose(arquivo);
    }

    printf("Nome: ");
    scanf(" %[^\n]", turma.nome);

    printf("Professor:\n");
    printf("Matrícula: ");
    scanf("%s", turma.professor.matricula);

    // Verifica se o professor está cadastrado
    arquivo = fopen("dados/professor/professores.bin", "rb");
    if (arquivo != NULL) {
        int professorEncontrado = 0;
        Professor professor;
        while (fread(&professor, sizeof(Professor), 1, arquivo)) {
            if (strcmp(professor.matricula, turma.professor.matricula) == 0) {
                professorEncontrado = 1;
                turma.professor = professor;
                break;
            }
        }
        fclose(arquivo);

        if (!professorEncontrado) {
            printf("Professor não encontrado!\n");
            return;
        }
    } else {
        printf("Não há professores cadastrados!\n");
        return;
    }

    turma.numAlunos = 0;
    turma.media = 0.0;

    arquivo = fopen("dados/turma/turmas.bin", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fwrite(&turma, sizeof(Turma), 1, arquivo);
    fclose(arquivo);

    printf("Turma cadastrada com sucesso!\n");
}




void imprimirTurmas() {
    Turma turma;
    FILE* arquivo = fopen("dados/turma/turmas.bin", "rb");

    printf("--- TURMAS CADASTRADAS ---\n");

    if (arquivo == NULL) {
        printf("Não há turmas cadastradas!\n");
        return;
    }

    while (fread(&turma, sizeof(Turma), 1, arquivo)) {
        printf("Código: %s\n", turma.codigo);
        printf("Nome: %s\n", turma.nome);
        printf("Professor:\n");
        printf("Matrícula: %s\n", turma.professor.matricula);
        printf("CPF: %s\n", turma.professor.cpf);
        printf("Nome: %s\n", turma.professor.nome);
        printf("Endereço:\n");
        printf("Logradouro: %s\n", turma.professor.endereco.logradouro);
        printf("Bairro: %s\n", turma.professor.endereco.bairro);
        printf("Cidade: %s\n", turma.professor.endereco.cidade);
        printf("Estado: %s\n", turma.professor.endereco.estado);
        printf("Número: %s\n", turma.professor.endereco.numero);
        printf("Alunos (%d):\n", turma.numAlunos);
        for (int i = 0; i < turma.numAlunos; i++) {
            printf("Matrícula: %s\n", turma.alunos[i].matricula);
            printf("CPF: %s\n", turma.alunos[i].cpf);
            printf("Nome: %s\n", turma.alunos[i].nome);
            printf("Endereço:\n");
            printf("Logradouro: %s\n", turma.alunos[i].endereco.logradouro);
            printf("Bairro: %s\n", turma.alunos[i].endereco.bairro);
            printf("Cidade: %s\n", turma.alunos[i].endereco.cidade);
            printf("Estado: %s\n", turma.alunos[i].endereco.estado);
            printf("Número: %s\n", turma.alunos[i].endereco.numero);
        }
        printf("Média: %.2f\n", turma.media);
        printf("------------\n");
    }

    fclose(arquivo);
}



void atualizarTurma() {
    char codigo[10];
    Turma turma;
    FILE* arquivo;
    long int posicao;

    printf("--- ATUALIZAÇÃO DE TURMA ---\n");
    printf("Código da turma a ser atualizada: ");
    scanf("%s", codigo);

    arquivo = fopen("dados/turma/turmas.bin", "r+b");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    while (fread(&turma, sizeof(Turma), 1, arquivo)) {
        if (strcmp(turma.codigo, codigo) == 0) {
            posicao = ftell(arquivo) - sizeof(Turma);
            fseek(arquivo, posicao, SEEK_SET);

            printf("Nome: ");
            scanf(" %[^\n]", turma.nome);

            printf("Professor:\n");
            printf("Matrícula: ");
            scanf("%s", turma.professor.matricula);

            // Verifica se o professor está cadastrado
            FILE* arquivoProfessores = fopen("dados/professor/professores.bin", "rb");
            if (arquivoProfessores != NULL) {
                int professorEncontrado = 0;
                Professor professor;
                while (fread(&professor, sizeof(Professor), 1, arquivoProfessores)) {
                    if (strcmp(professor.matricula, turma.professor.matricula) == 0) {
                        professorEncontrado = 1;
                        turma.professor = professor;
                        break;
                    }
                }
                fclose(arquivoProfessores);

                if (!professorEncontrado) {
                    printf("Professor não encontrado!\n");
                    return;
                }
            } else {
                printf("Não há professores cadastrados!\n");
                return;
            }

            fwrite(&turma, sizeof(Turma), 1, arquivo);
            fclose(arquivo);

            printf("Turma atualizada com sucesso!\n");
            return;
        }
    }

    fclose(arquivo);
    printf("Turma não encontrada!\n");
}



void descadastrarTurma() {
    char codigo[10];
    Turma turma;
    FILE* arquivo;
    int turmaEncontrada = 0;

    printf("--- DESCADASTRAR TURMA ---\n");
    printf("Código da turma a ser descadastrada: ");
    scanf("%s", codigo);

    arquivo = fopen("dados/turma/turmas.bin", "r+b");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    FILE* arquivoTemporario = fopen("dados/turma/turmas_temp.bin", "w+b");
    if (arquivoTemporario == NULL) {
        printf("Erro ao abrir o arquivo temporário!\n");
        fclose(arquivo);
        return;
    }

    while (fread(&turma, sizeof(Turma), 1, arquivo)) {
        if (strcmp(turma.codigo, codigo) == 0) {
            turmaEncontrada = 1;
        } else {
            fwrite(&turma, sizeof(Turma), 1, arquivoTemporario);
        }
    }

    fclose(arquivo);
    fclose(arquivoTemporario);

    if (turmaEncontrada) {
        remove("dados/turma/turmas.bin");
        rename("dados/turma/turmas_temp.bin", "dados/turma/turmas.bin");
        printf("Turma descadastrada com sucesso!\n");
    } else {
        remove("dados/turma/turmas_temp.bin");
        printf("Turma não encontrada!\n");
    }
}



void calcularMediaTurmas() {
    FILE* arquivoTurmas = fopen("dados/turma/turmas.bin", "rb");
    if (arquivoTurmas == NULL) {
        printf("Não há turmas cadastradas!\n");
        return;
    }

    Turma turma;
    float somaMedias = 0.0;
    int numTurmas = 0;

    printf("--- MÉDIA DAS TURMAS ---\n");

    while (fread(&turma, sizeof(Turma), 1, arquivoTurmas)) {
        somaMedias += turma.media;
        numTurmas++;
    }

    fclose(arquivoTurmas);

    if (numTurmas > 0) {
        float mediaTurmas = somaMedias / numTurmas;
        printf("Média de todas as turmas: %.2f\n", mediaTurmas);
    } else {
        printf("Não há turmas cadastradas!\n");
    }
}
