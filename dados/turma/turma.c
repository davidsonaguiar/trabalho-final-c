#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./turma.h"

void cadastrarTurma() {
    Turma turma;
    FILE* arquivo;

    printf("--- CADASTRO DE TURMA ---\n");

    // Input para usuario informar o codigo da turma
    printf("Código: ");
    scanf("%s", turma.codigo);

    // O arquivo dados/turma/turmas.bin e aberto para verificar se o condigo ja esta cadastrado
    arquivo = fopen("dados/turma/turmas.bin", "rb");

    if (arquivo != NULL) {
        Turma turmaExistente;
        // Loop para percorrer as turmas cadastradas
        // Verifica se o codigo ja esta cadastrado      
        while (fread(&turmaExistente, sizeof(Turma), 1, arquivo)) {
            // Se o codigo da turma cadastrada for igual ao codigo informado
            // O sistema retorna a msg Turma ja cadastrada
            if (strcmp(turmaExistente.codigo, turma.codigo) == 0) {
                printf("Turma já cadastrada!\n");
                // chamento do arquivo
                fclose(arquivo);
                // retorna vazio e a funcao e encerrada
                return;
            }
        }

        // Caso o condigo nao seja localizado o arquivo e fechado
        fclose(arquivo);
    }

    // Input para o usuario informar o nome da turma
    printf("Nome: ");
    scanf(" %[^\n]", turma.nome);

    // Input para o usuario informar a matricula do professor
    printf("Professor:\n");
    printf("Matrícula: ");
    scanf("%s", turma.professor.matricula);

    // Input para o usuario informar a matricula do professor
    printf("Media da turma: ");
    scanf("%f", &turma.media);

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
        printf("=================================================\n");
        printf(" %s - %s   Media: %.2f\n", turma.nome, turma.codigo, turma.media);
        printf("=================================================\n");
        printf("-------------------------------------------------\n");
        printf("Professor:\n");
        printf("-------------------------------------------------\n");
        printf("   Matrícula: %s\n", turma.professor.matricula);
        printf("   CPF: %s\n", turma.professor.cpf);
        printf("   Nome: %s\n", turma.professor.nome);
        printf("-------------------------------------------------\n");
        printf("Alunos (%d):\n", turma.numAlunos);
        printf("-------------------------------------------------\n");
        for (int i = 0; i < turma.numAlunos; i++) {
            printf("   Matrícula: %s\n", turma.alunos[i].matricula);
            printf("   CPF: %s\n", turma.alunos[i].cpf);
            printf("   Nome: %s\n", turma.alunos[i].nome);
            printf("   ----------------------------------------------\n");

        }
        printf("-------------------------------------------------\n");
        printf("Média: %.2f\n", turma.media);
        printf("-------------------------------------------------\n");
        printf("\n");
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
        rename("dados/turma/turmas_temp.bin", "dados/turma/dados/turma/turmas.bin");
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


void adicionarAluno() {
    char codigo[10], matricula[10];
    FILE* arquivoTurmas;
    FILE* arquivoAlunos;
    Turma turma;
    Aluno aluno;
    int turmaEncontrada = 0, alunoEncontrado = 0;

    printf("--- ADICIONAR ALUNO A UMA TURMA ---\n");

    // Input para receber o codigo da turma
    printf("Código da turma: ");
    scanf("%s", codigo);

    // Abrindo o arquivo dados/turma/turmas.bin para verificacao
    arquivoTurmas = fopen("dados/turma/turmas.bin", "r+b");

    // Caso ocorra erro retorna a msg abaixo
    if (arquivoTurmas == NULL) {
        printf("Erro ao abrir o arquivo de turmas!\n");
        return;
    }

    // Loop para percorrer cada turma registrada no arquivo dados/turma/turmas.bin
    while (fread(&turma, sizeof(Turma), 1, arquivoTurmas)) {
        // Se o codigo for localizado turmaEncontrada sera true
        if (strcmp(turma.codigo, codigo) == 0) {

            turmaEncontrada = 1;
            break;
        }
    }

    // Se a turma nao for localizado a funcao e encerrada e imprimi msg baixo
    if (!turmaEncontrada) {
        printf("Turma não encontrada!\n");
        // fechamento do arquivo
        fclose(arquivoTurmas);
        return;
    }

    // Input para receber a matricula do aluno
    printf("Matrícula do aluno: ");
    scanf("%s", matricula);

    // Abrindo o arquivo dados/aluno/alunos.bin para verificacao
    arquivoAlunos = fopen("dados/aluno/alunos.bin", "r+b");

    // Caso ocorra erro retorna a msg abaixo
    if (arquivoAlunos == NULL) {
        printf("Erro ao abrir o arquivo de alunos!\n");
        fclose(arquivoTurmas);
        return;
    }

    // Loop para percorrer cada aluno registrado no arquivo dados/aluno/alunos.bin
    while (fread(&aluno, sizeof(Aluno), 1, arquivoAlunos)) {
        // Se o codigo for localizado alunoEncontrado sera true
        if (strcmp(aluno.matricula, matricula) == 0) {
            alunoEncontrado = 1;
            break;
        }
    }

    // Verfica se aluno nao foi encontrado
    if (!alunoEncontrado) {
        // se condicao acima for verdadeira retornar a msg abaixo
        printf("Aluno não encontrado!\n");
        // fechamento dos arquivos turmas e alunos .bin
        fclose(arquivoTurmas);
        fclose(arquivoAlunos);
        return;
    }

    // loop para percorrer cada aluno da turma encontrada
    for (int i = 0; i < turma.numAlunos; i++) {
        // verifica se a matricula ja esta cadastrada
        if (strcmp(turma.alunos[i].matricula, matricula) == 0) {
            // Se a matricula informada for igual a de algum aluni cadastrado retorna a msg abaixo
            printf("O aluno já está cadastrado na turma!\n");
            // Fechamento dos arquivos bin
            fclose(arquivoTurmas);
            fclose(arquivoAlunos);
            // retorna vazio
            return;
        }
    }

    // Condicacao para verifica se atingiu o numero maximo de alunos
    if (turma.numAlunos >= 40) {
        printf("A turma já está com a capacidade máxima de alunos!\n");
        fclose(arquivoTurmas);
        fclose(arquivoAlunos);
        return;
    }

    // adicionando dados do aluno na turma
    strcpy(turma.alunos[turma.numAlunos].matricula, aluno.matricula);
    strcpy(turma.alunos[turma.numAlunos].cpf, aluno.cpf);
    strcpy(turma.alunos[turma.numAlunos].nome, aluno.nome);
    strcpy(turma.alunos[turma.numAlunos].endereco.logradouro, aluno.endereco.logradouro);
    strcpy(turma.alunos[turma.numAlunos].endereco.bairro, aluno.endereco.bairro);
    strcpy(turma.alunos[turma.numAlunos].endereco.cidade, aluno.endereco.cidade);
    strcpy(turma.alunos[turma.numAlunos].endereco.estado, aluno.endereco.estado);
    strcpy(turma.alunos[turma.numAlunos].endereco.numero, aluno.endereco.numero);

    // adicionando +1 ao numero de alunos
    turma.numAlunos++;

    // Posicionando o local de escrita no arquivo dados/turma/turmas.bin
    fseek(arquivoTurmas, -sizeof(Turma), SEEK_CUR);

    // Adicionando aluno no arquivo
    fwrite(&turma, sizeof(Turma), 1, arquivoTurmas);

    // msg de sucesso
    printf("Aluno adicionado à turma com sucesso!\n");

    //fechamento dos arquivos bin
    fclose(arquivoTurmas);
    fclose(arquivoAlunos);
}


void imprimirMedia() {
    Turma turma;
    int quantidadeTurmas = 0;
    float somatorioNotas = 0;

    FILE* arquivoTurma = fopen("dados/turma/turmas.bin", "rb");

    if(arquivoTurma == NULL) {
        printf("Erro ao abrir arquivo .bin");
        fclose(arquivoTurma);
    }

    while(fread(&turma, sizeof(Turma), 1, arquivoTurma)) {
        quantidadeTurmas++;
        somatorioNotas += turma.media;
    }

    printf("=================================================\n");
    printf("Media das Turmas\n");
    printf("=================================================\n");
    printf("MEDIA: %.2f.\n", somatorioNotas / quantidadeTurmas);
    printf("-------------------------------------------------");

    fclose(arquivoTurma);
}