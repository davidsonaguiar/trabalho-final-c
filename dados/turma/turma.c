#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./turma.h"

// Funco para criar e adicionar uma turma no arquivo turmas.bin
void cadastrarTurma() {

    Turma turma;
    FILE* arquivo;

    printf("--- CADASTRO DE TURMA ---\n");

    // Input para usuario informar o codigo da turma
    printf("Código: ");
    scanf("%s", turma.codigo);

    // O arquivo dados/turma/turmas.bin e aberto para verificar se o condigo ja esta cadastrado
    arquivo = fopen("dados/turma/turmas.bin", "rb");

    // Verifica se nao houve problema para abrir o arquivo turmas.bin
    if (arquivo != NULL) {
        Turma turmaExistente;
        // Loop para percorrer as turmas cadastradas
        // Verifica se o codigo ja esta cadastrado      
        while (fread(&turmaExistente, sizeof(Turma), 1, arquivo)) {
            // Se o codigo da turma cadastrada for igual ao codigo informado
            // O sistema retorna a msg Turma ja cadastrada
            if (strcmp(turmaExistente.codigo, turma.codigo) == 0) {
                printf("Turma já cadastrada!\n");
                // fechamento do arquivo
                fclose(arquivo);
                // retorna vazio e a funcao e encerrada
                return;
            }
        }

        // Caso o codigo ainda nao exista 
        // O arquivo e fechado
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

    // Abertura do arquivo professores.bin para verificacao
    arquivo = fopen("dados/professor/professores.bin", "rb");

    // Verifica se nao houve problema para abrir o arquivo professores.bin
    if (arquivo != NULL) {
        int professorEncontrado = 0; //variavel para verificar se o professor foi encontrado
        Professor professor;

        // Loop para percorrer os professores cadastrados
        // Verifica se a matricula existe            
        while (fread(&professor, sizeof(Professor), 1, arquivo)) {
            if (strcmp(professor.matricula, turma.professor.matricula) == 0) {
                // Se a matricula for encontrada professor recebe 1(true)
                professorEncontrado = 1;
                // atribuido progessor a turma
                turma.professor = professor;
                // Quebrando o laco
                break;
            }
        }
        // Fechamento do arquivo
        fclose(arquivo);

        // Caso o arquivo nao seja localizado retorna a msg abaixo
        if (!professorEncontrado) {
            printf("Professor não encontrado!\n");
            return;
        }
    } else {
        // Caso o arquivo nao seja localizado retorna a msg abaixo
        printf("Não há professores cadastrados!\n");
        return;
    }

    // Inicialmente o numero de alunos sera 0
    turma.numAlunos = 0;

    // Abertura do arquivo turmas.bin para adicionar a turma
    arquivo = fopen("dados/turma/turmas.bin", "ab");

    // Caso nao consiga, printa a msg abaixo
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Salvando turma no arquivo turmas.bin
    fwrite(&turma, sizeof(Turma), 1, arquivo);
    //fechando arquivo
    fclose(arquivo);
    // msg de sucesso
    printf("Turma cadastrada com sucesso!\n");
}



// Funcao para imprimir todos as turmas cadastradas no arquivo turmas.bin
void imprimirTurmas() {
    Turma turma;

    // Abrindo o arquivo turmas.bin
    FILE* arquivo = fopen("dados/turma/turmas.bin", "rb");

    printf("--- TURMAS CADASTRADAS ---\n");

    // Caso nao consiga abrir o arquivo a msg abaixo sera impressa
    if (arquivo == NULL) {
        printf("Não há turmas cadastradas!\n");
        return;
    }

    // Verifica se a alguma turma cadastrada
    if(fread(&turma, sizeof(Turma), 1, arquivo) == 0) {
        // Caso nao tenha turma cadastrada print a msg abaixo
        printf("Não há turmas cadastradas!\n");
    } else {
        // Retorna o ponteiro para o inicio do arquivo
        fseek(arquivo, 0, SEEK_SET);

        // Loop para percorrer cada turma salva no arquivo turmas.bin
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
    }
    // Fechamento do arquivo
    fclose(arquivo);
}


// Funcao para atualizar as turmas 
void atualizarTurma() {
    char codigo[10];
    Turma turma;
    FILE* arquivo;
    long int posicao;

    printf("--- ATUALIZAÇÃO DE TURMA ---\n");

    // Input para usuario informa o codigo da turma que deseja alterar
    printf("Código da turma a ser atualizada: ");
    scanf("%s", codigo);

    // Abertura do arquivo turmas.bin
    arquivo = fopen("dados/turma/turmas.bin", "r+b");
    // Caso nao consigo abrir printa a msg abaixo
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        // funcao retorna vazio
        return;
    }

    // Loop para ler cada turma no arquivo turmas.bin
    while (fread(&turma, sizeof(Turma), 1, arquivo)) {
        // Caso o codigo da turma lida e o codigo digitado pelo usuario sejam iguais
        if (strcmp(turma.codigo, codigo) == 0) {
            // Obter a posicao do ultimo registro lido e salvar na variavel posicao
            posicao = ftell(arquivo) - sizeof(Turma);
            // Posiciona o ponteiro para do ultimo registro lido
            fseek(arquivo, posicao, SEEK_SET);

            // Solicita o nome da turma
            printf("Nome: ");
            scanf(" %[^\n]", turma.nome);
            
            // Solicita o nome do professor
            printf("Professor:\n");
            printf("Matrícula: ");
            scanf("%s", turma.professor.matricula);

            // abertura do arquivo professores.bin
            FILE* arquivoProfessores = fopen("dados/professor/professores.bin", "rb");

            // Verifica se nao houve problema para abrir o arquivo
            if (arquivoProfessores != NULL) {
                int professorEncontrado = 0;
                Professor professor;
                // Loop para ler cada professor no arquivo professores.bin
                while (fread(&professor, sizeof(Professor), 1, arquivoProfessores)) {
                    // Verifica se a matricula do professor e igual a matricula informada
                    if (strcmp(professor.matricula, turma.professor.matricula) == 0) {
                        // caso seja igual a variavel professor encontrado receber 1 (true)
                        professorEncontrado = 1;
                        // atribui o professor a turma
                        turma.professor = professor;
                        break;
                    }
                }

                // Fechamento do arquivo
                fclose(arquivoProfessores);

                // Caso professor nao seja encontrado a msg abaixo e impressa
                if (!professorEncontrado) {
                    printf("Professor não encontrado!\n");
                    return;
                }
            // caso ocorra erro na abertura do arquivo imprime a msg abaixo
            } else {
                printf("Não há professores cadastrados!\n");
                return;
            }

            // solicita a media da turma
            printf("Media da Turma: ");
            scanf("%f", &turma.media);

            // salva a turma atualizada no arquivo turmas.bin
            fwrite(&turma, sizeof(Turma), 1, arquivo);
            // fechamento do arquivo 
            fclose(arquivo);
            // msg de sucesso
            printf("Turma atualizada com sucesso!\n");
            return;
        }
    }

    // fechamento do arquivo
    fclose(arquivo);
    // msg caso nao localize o arquivo
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