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



// Deletar turma
void descadastrarTurma() {
    char codigo[10];
    Turma turma;
    FILE* arquivo;
    int turmaEncontrada = 0;

    printf("--- DESCADASTRAR TURMA ---\n");

    // Input solicitando o codigo da turma
    printf("Código da turma a ser descadastrada: ");
    scanf("%s", codigo);

    // Abertura do arquivo turmas.bin
    arquivo = fopen("dados/turma/turmas.bin", "r+b");

    // Caso ocorra erro na abertura do arquivo printa a msg abaixo
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Abertura do arquivo turmas_temp.bin
    FILE* arquivoTemporario = fopen("dados/turma/turmas_temp.bin", "w+b");

    // Caso ocorra erro na abertura do arquivo printa a msg abaixo
    if (arquivoTemporario == NULL) {
        printf("Erro ao abrir o arquivo temporário!\n");
        // fechamento do arquivo
        fclose(arquivo);
        return;
    }

    // Percorre cada turma cadastrada no arquivo .bin
    while (fread(&turma, sizeof(Turma), 1, arquivo)) {
        // Se o codigo informado for igual ao codigo da turma
        if (strcmp(turma.codigo, codigo) == 0) {
            // A variavel turmaEncontrada recebe 1 (true)
            turmaEncontrada = 1;
        } else {
            // Se o codigo nao for igual salva a turma no arquivo temporario
            fwrite(&turma, sizeof(Turma), 1, arquivoTemporario);
        }
    }

    // fechamento dos arquivos turmas e temporario .bin
    fclose(arquivo);
    fclose(arquivoTemporario);

    // Se turma for encontrada
    if (turmaEncontrada) {
        // Excluir o arquivo turmas.bin
        remove("dados/turma/turmas.bin");
        // Renomeia o arquivo turmas_temp.bin para turmas.bin
        rename("dados/turma/turmas_temp.bin", "dados/turma/dados/turma/turmas.bin");
        // Imprime a msg de sucesso
        printf("Turma descadastrada com sucesso!\n");
    // Se nao encontrar a turma
    } else {
        // Remove o arquivo turmas_temp.bin
        remove("dados/turma/turmas_temp.bin");
        // Imprime msg de nao encontrada
        printf("Turma não encontrada!\n");
    }
}


// Cadastrar aluno na turma
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

    // Abertura do arquivo turmas.bin
    FILE* arquivoTurma = fopen("dados/turma/turmas.bin", "rb");

    // Caso ocorra erro na abertura do arquivo
    if(arquivoTurma == NULL) {
        // Imprime a msg abaixo
        printf("Erro ao abrir arquivo turmas.bin");
        // Fecha o arquivo turmas.bin
        fclose(arquivoTurma);
    }

    // Percorre todas as turmas cadastrada no arquivo turmas.bin
    while(fread(&turma, sizeof(Turma), 1, arquivoTurma)) {
        // incrementa +1 a quantidade de turma
        quantidadeTurmas++;
        // adiciona o valor da media da turma a variavel somatorioNotas
        somatorioNotas += turma.media;
    }

    printf("=================================================\n");
    printf("Media das Turmas\n");
    printf("=================================================\n");
    // Imprime a divisao do somatorio / quantidade de turmas
    printf("MEDIA: %.2f.\n", somatorioNotas / quantidadeTurmas);
    printf("-------------------------------------------------");

    // Fechamento do arquivo 
    fclose(arquivoTurma);
}


// Remover aluno da turma
void descadastrarAlunoTurma() {
    Turma turma, turmaTemp;
    int alunoEncontrado = 0;
    char codigoTurma[10];
    char matriculaAluno[10];

    // Solicita codigo da turma
    printf("Digite o código da turma: ");
    scanf("%s", codigoTurma);
    // Solicita matricula do aluno
    printf("Digite a matrícula do aluno: ");
    scanf("%s", matriculaAluno);

    // Abertur dos arquivos turmas.bin e temporario.bin
    FILE* arquivoTurmas = fopen("dados/turma/turmas.bin", "rb");
    FILE* arquivoTemp = fopen("dados/turma/temporario.bin", "wb");

    // Caso ocorra erro na abertura do arquivo imprime a msg abaixo
    if (arquivoTurmas == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir os arquivos de turmas ou temporário!\n");
        return;
    }

    // Percorre cada turma cadastrada no arquivo turmas.bin
    while (fread(&turma, sizeof(Turma), 1, arquivoTurmas)) {
        // Se o codigo da turma for diferente ao codigo informado
        if (strcmp(turma.codigo, codigoTurma) == 0) {
            // Copiando os dados da turma para turma_temporaria
            strcpy(turmaTemp.codigo, turma.codigo);
            strcpy(turmaTemp.nome, turma.nome);
            turmaTemp.numAlunos = 0;
            turmaTemp.media = turma.media;
            turmaTemp.professor = turma.professor;

            // Percorre todos os aluno da turma
            for (int i = 0; i < turma.numAlunos; i++) {
                // Verifica se a matricula do aluno e diferente da matricula informada
                if (strcmp(turma.alunos[i].matricula, matriculaAluno) != 0) {
                    // Copiando os dados para a turmaTemp
                    strcpy(turmaTemp.alunos[turmaTemp.numAlunos].nome, turma.alunos[i].nome);
                    strcpy(turmaTemp.alunos[turmaTemp.numAlunos].cpf, turma.alunos[i].cpf);
                    strcpy(turmaTemp.alunos[turmaTemp.numAlunos].matricula, turma.alunos[i].matricula);
                    turmaTemp.alunos[turmaTemp.numAlunos].endereco = turma.alunos[i].endereco;
                    turmaTemp.numAlunos++;
                } else {
                    alunoEncontrado = 1;
                }
            }
            //Salvando a turmaTemp no arquivo .bin
            fwrite(&turmaTemp, sizeof(Turma), 1, arquivoTemp);
        } else {
            //Salvando a turma no arquivo .bin
            fwrite(&turma, sizeof(Turma), 1, arquivoTemp);
        }
    }

    // Fechamento dos arquivos
    fclose(arquivoTurmas);
    fclose(arquivoTemp);

    // Remove o arquivo turmas.bin
    remove("dados/turma/turmas.bin");
    // Renomea o arquivo temporario.bin para turmas.bin
    rename("dados/turma/temporario.bin", "dados/turma/turmas.bin");


    if (alunoEncontrado) {
        printf("Aluno descadastrado da turma com sucesso!\n");
    } else {
        printf("Aluno não encontrado na turma!\n");
    }
}
