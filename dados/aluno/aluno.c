#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./aluno.h" // Importando o cabecalho com os tipos, constantes e funcoes do aluno.

void cadastrarAluno() {
    Aluno aluno;
    FILE* arquivo; 

    printf("--- CADASTRO DE ALUNO ---\n");

    // Input da Matricula e CPF para verificar se os dados ja 
    // foram cadastrados no alunos.bin
    printf("Matrícula: ");
    scanf("%s", aluno.matricula);

    printf("CPF: ");
    scanf("%s", aluno.cpf);

    // Abertura do arquivo alunos.bin no diretorio dados/aluno/ para verificao
    arquivo = fopen("dados/aluno/alunos.bin", "rb");

    // Verifica se o aluno ja esta cadastrado no arquivo alunos.bin    
    if (arquivo != NULL) {

        Aluno alunoExistente;
        // Loop para consultar cada aluno no alunos.bin
        while (fread(&alunoExistente, sizeof(Aluno), 1, arquivo)) {
            // CPF e Matricula informados sao comparados com cada aluno ja cadastrado no sistema
            if (strcmp(alunoExistente.matricula, aluno.matricula) == 0 || strcmp(alunoExistente.cpf, aluno.cpf) == 0) {
                // Se o CPF ou Matricula informado constar cadastrado retorna a msg abaixo
                printf("Aluno já cadastrado no sistema!\n");
                // O arquivo e fechado
                fclose(arquivo);
                // A funcao sera parada return vazio
                return;
            }
        }
        // fechamento do arquivo caso nao seja identificada a matricula ou cpf
        fclose(arquivo);
    }

    // Se caso a verificacao nao encontre a matricula ou cpf e solicitado o restante dos dados
    printf("Nome: ");
    scanf(" %[^\n]", aluno.nome);
    printf("Endereço:\n");
    printf("Logradouro: ");
    scanf(" %[^\n]", aluno.endereco.logradouro);
    printf("Bairro: ");
    scanf(" %[^\n]", aluno.endereco.bairro);
    printf("Cidade: ");
    scanf(" %[^\n]", aluno.endereco.cidade);
    printf("Estado: ");
    scanf(" %[^\n]", aluno.endereco.estado);
    printf("Número: ");
    scanf(" %[^\n]", aluno.endereco.numero);

    // Abertura do arquivo alunos.bin no diretorio dados/aluno/ para adicao do novo aluno
    arquivo = fopen("dados/aluno/alunos.bin", "ab");

    // Se nao consegui abrir o arquivo retorna a msg abaixo
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Adicionando aluno no arquivo alunos.bin
    fwrite(&aluno, sizeof(Aluno), 1, arquivo);
    fclose(arquivo);

    // Msg para informar que o aluno foi cadastrado com sucesso
    printf("Aluno cadastrado com sucesso!\n");
}


void imprimirAlunos() {
    Aluno aluno;

    // Abertura do arquivo alunos.bin no diretorio dados/aluno/ para leitura modulp rb
    FILE* arquivo = fopen("dados/aluno/alunos.bin", "rb");

    printf("--- ALUNOS CADASTRADOS ---\n");

    // Se nao consegui abrir o arquivo retorna a msg abaixo
    if (arquivo == NULL) {
        printf("Não há alunos cadastrados!\n");
        return;
    }

    // Loop para ler cada aluno salvo em alunos.bin
    // a cada loop e consultado um bloco do tamanho de Aluno
    // e salvo em &aluno

    if(fread(&aluno, sizeof(Aluno), 1, arquivo) == 0) {
        printf("Não há alunos cadastrados!\n");
    } else {
        fseek(arquivo, 0, SEEK_SET);

        while (fread(&aluno, sizeof(Aluno), 1, arquivo)) {
            printf("Matrícula: %s\n", aluno.matricula);
            printf("CPF: %s\n", aluno.cpf);
            printf("Nome: %s\n", aluno.nome);
            printf("Endereço:\n");
            printf("Logradouro: %s\n", aluno.endereco.logradouro);
            printf("Bairro: %s\n", aluno.endereco.bairro);
            printf("Cidade: %s\n", aluno.endereco.cidade);
            printf("Estado: %s\n", aluno.endereco.estado);
            printf("Número: %s\n", aluno.endereco.numero);
            printf("------------\n");
        }
    }


    // Fechamento do arquivo
    fclose(arquivo);
}


void atualizarAluno() {
    char matricula[10];
    Aluno aluno;
    FILE* arquivo;
    long int posicao;

    printf("--- ATUALIZAÇÃO DE ALUNO ---\n");

    // Input da matricula que sera verificada
    printf("Matrícula do aluno a ser atualizado: ");
    scanf("%s", matricula);

    // Abertura do arquivo alunos.bin no diretorio dados/aluno/ para leitura
    arquivo = fopen("dados/aluno/alunos.bin", "r+b");

    // Se nao consegui abrir o arquivo retorna a msg abaixo
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Loop para ler cada aluno salvo em alunos.bin
    // a cada loop e consultado um bloco do tamanho de Aluno
    // e salvo em &aluno
    while (fread(&aluno, sizeof(Aluno), 1, arquivo)) {
        // comparando se a matricula informado ja consta cadastrada
        if (strcmp(aluno.matricula, matricula) == 0) {
            // Verificando a posicao do ponteiro do aluno com a matricula informada
            posicao = ftell(arquivo) - sizeof(Aluno);
            // Movendo a o local de escrita no arquivo para a posicao acima
            fseek(arquivo, posicao, SEEK_SET);

            // Solicitando os dados para edicao
            printf("CPF: ");
            scanf("%s", aluno.cpf);
            printf("Nome: ");
            scanf(" %[^\n]", aluno.nome);
            printf("Endereço:\n");
            printf("Logradouro: ");
            scanf(" %[^\n]", aluno.endereco.logradouro);
            printf("Bairro: ");
            scanf(" %[^\n]", aluno.endereco.bairro);
            printf("Cidade: ");
            scanf(" %[^\n]", aluno.endereco.cidade);
            printf("Estado: ");
            scanf(" %[^\n]", aluno.endereco.estado);
            printf("Número: ");
            scanf(" %[^\n]", aluno.endereco.numero);

            // Salvando os dados informados
            fwrite(&aluno, sizeof(Aluno), 1, arquivo);

            // Fecchando arquivo
            fclose(arquivo);

            // msg de sucesso
            printf("Aluno atualizado com sucesso!\n");

            return;
        }
    }

    fclose(arquivo);
    printf("Aluno não encontrado!\n");
}


void descadastrarAluno() {
    char matricula[10];
    Aluno aluno;
    FILE* arquivo;
    FILE* arquivoTurmas;
    int alunoEncontrado = 0;

    printf("--- DESCADASTRAR ALUNO ---\n");

    // Solicitando a matricula do aluno que sera descadastrado
    printf("Matrícula do aluno a ser descadastrado: ");
    scanf("%s", matricula);

    // Abertura do arquivo turmas.bin para leitura e verificar se o aluno esta cadastrado em aluma turma
    arquivoTurmas = fopen("dados/turma/turmas.bin", "rb");

    // Verifica se conseguiu abrir o arquivo
    if (arquivoTurmas != NULL) {
        Turma turma;

        // Loop para consultar se cada turma
        while (fread(&turma, sizeof(Turma), 1, arquivoTurmas)) {
            
            // Loop para consultar cada aluno na turma
            for (int i = 0; i < turma.numAlunos; i++) {
                // Verifica se a matricula informada e igual a do aluno cadastrado
                if (strcmp(turma.alunos[i].matricula, matricula) == 0) {
                    // Se a condicao acima for verdadeira imprimir a msg abaixo
                    printf("O aluno está associado à turma %s. Não é possível descadastrá-lo!\n", turma.codigo);
                    // O arquivo e fechado
                    fclose(arquivoTurmas);
                    // A funcao e encerrada e retorna vazio
                    return;
                }
            }
        }

        fclose(arquivoTurmas);
    }

    // Caso a verificao acima retorne false
    // O arquivo alunos.bin e aberto para leitura
    arquivo = fopen("dados/aluno/alunos.bin", "r+b");

    // Caso nao consiga abrir apresentara uma msg de erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // E aberto um arquivo temporario para substituir alunos.bin
    FILE* arquivoTemporario = fopen("dados/aluno/alunos_temp.bin", "w+b");

    // Caso nao consiga abrir apresentara uma msg de erro
    if (arquivoTemporario == NULL) {
        printf("Erro ao abrir o arquivo temporário!\n");
        fclose(arquivo);
        return;
    }

    // Loop para verificar cada aluno
    while (fread(&aluno, sizeof(Aluno), 1, arquivo)) {
        // verifica se a matricula do aluno cadastrado e igual a matricula informada
        if (strcmp(aluno.matricula, matricula) == 0) {
            // Se a condicao acima for verdadeira entao o aluno ja e cadstrado
            alunoEncontrado = 1;
        } else {
            // Se nao o aluno sera escrito no arquivo temporario
            fwrite(&aluno, sizeof(Aluno), 1, arquivoTemporario);
        }
    }

    // Fechamento dos arquivos alunos.bin e temp.bin
    fclose(arquivo);
    fclose(arquivoTemporario);

    // Se o aluno for encontrado
    // aluno.bin e removido
    // alunos_temp.bin e renomeado para alunos.bin
    // se nao o arquivo temporario e removido
    if (alunoEncontrado) {
        remove("dados/aluno/alunos.bin");
        rename("dados/aluno/alunos_temp.bin", "dados/aluno/alunos.bin");
        printf("Aluno descadastrado com sucesso!\n");
    } else {
        remove("dados/aluno/alunos_temp.bin");
        printf("Aluno não encontrado!\n");
    }
}