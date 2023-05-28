#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./professor.h" // Importando o cabeçalho do professor, com sua fuções, tipos e constantes. 

//sistema de cadastro e gerenciamento de informações de professores
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

    // O arquivo dados/professor/professor.bin e aberto para verificar se o condigo ja esta cadastrado
    // Verifica se o professor já está cadastrado
    arquivo = fopen("dados/professor/professores.bin", "rb");
    if (arquivo != NULL) {
        // Loop para percorrer os professores cadastrados
        // Verifica se o codigo ja esta cadastrado   
        Professor professorExistente;
        while (fread(&professorExistente, sizeof(Professor), 1, arquivo)) {
            // Se o codigo do professor cadastrada for igual ao codigo informado
            // O sistema retorna a msg Turma ja cadastrada
            if (strcmp(professorExistente.matricula, professor.matricula) == 0 || strcmp(professorExistente.cpf, professor.cpf) == 0) {
                printf("Professor já cadastrado!\n");
                //frchando arquivo e função encerra
                fclose(arquivo);
                return;
            }
        }
        // caso o codigo não seja localizado o arquivo é fechado
        fclose(arquivo);
    }

    // menu para inserir informações do professor.
    // inserir nome do professor pelo o usuario.
    printf("Nome: ");
    scanf(" %[^\n]", professor.nome);
    //inserir endereço/logradouro
    printf("Endereço:\n");
    printf("Logradouro: ");
    scanf(" %[^\n]", professor.endereco.logradouro);
    //inserir bairro
    printf("Bairro: ");
    scanf(" %[^\n]", professor.endereco.bairro);
    //inseirir cidade.
    printf("Cidade: ");
    scanf(" %[^\n]", professor.endereco.cidade);
    //inseiri estado.
    printf("Estado: ");
    scanf(" %[^\n]", professor.endereco.estado);
    //inserir numero.
    printf("Número: ");
    scanf(" %[^\n]", professor.endereco.numero);
    //abrir arquivo de professor, para adicionar um novo.
    arquivo = fopen("dados/professor/professores.bin", "ab");
    // se não abrir apresentar a mensagem abaixo.
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    // adicionando professor ao arquivo de professores.bin
    fwrite(&professor, sizeof(Professor), 1, arquivo);
    fclose(arquivo);
     // mensagem para informar que o professor foi cadastrado com sucesso
    printf("Professor cadastrado com sucesso!\n");
}


//sistema para imprimir professores cadastrado.
void imprimirProfessores() {
    Professor professor;
    //abrir arquivo de professores
    FILE* arquivo = fopen("dados/professor/professores.bin", "rb");
     //menu do professores cadastrados.
    printf("--- PROFESSORES CADASTRADOS ---\n");
//se não ouver professores cadastrado no arquivo .bin, apresentar a mensagem. 
    if (arquivo == NULL) {    
        printf("Não há professores cadastrados!\n");
        return;
    }
//loop para verificar se a professores cadastrados.
//verifica se há pelo menos um registro de professor no arquivo usando.
//Se o resultado dessa chamada for zero, significa que não há professores cadastrados e imprimi a mensagem.
//se ouver professores entrar no loop e imprimir as informações.
//se ouver professores entrar no loop e imprimir as informações
    if(fread(&professor, sizeof(Professor), 1, arquivo) == 0) {
        printf("Não há professorres cadastrados!\n");
    } else {
        fseek(arquivo, 0, SEEK_SET);
        
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
//fehcamento de arquivo.
    fclose(arquivo);
}


//sistema de atualização de professores
void atualizarProfessor() {
    char matricula[10];
    Professor professor;
    FILE* arquivo;
    long int posicao;
 //menu.
    printf("--- ATUALIZAÇÃO DE PROFESSOR ---\n");
    //input para verificação de matricula do professor
    printf("Matrícula do professor a ser atualizado: ");
    scanf("%s", matricula);
 //abertura do arquivo professor.bin, para leitura de dados.
    arquivo = fopen("dados/professor/professores.bin", "r+b");
    //condição para caso não abra o arquivo.
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
 //loop para ler professores salvos no arquivo bin.
    //a cada loop é verificado um bloco do tamnho de professores e salvo em %professor.
    while (fread(&professor, sizeof(Professor), 1, arquivo)) {
         //comparar se já existe a matricula informada.
        if (strcmp(professor.matricula, matricula) == 0) {
            //verificando a posição do ponteiro do aluno com a matricula.
            posicao = ftell(arquivo) - sizeof(Professor);
            //movendo o local de escrita no arquivo para a posição acima.
            fseek(arquivo, posicao, SEEK_SET);
 //solicitando dados ao usuario.
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
 //salvar dados informado.
            fwrite(&professor, sizeof(Professor), 1, arquivo);
            //fechando arquivo
            fclose(arquivo);
 //mensagem de sucesso.
            printf("Professor atualizado com sucesso!\n");
            return;
        }
    }
//fechar arquivo.
    fclose(arquivo);
     //caso a matricula do professor informado não seja encotrado, exibir.
    printf("Professor não encontrado!\n");
}


//sistema de remover professores.
void descadastrarProfessor() {
    //declaração de varivel para solicitação de numero da matricula.
    char matricula[10];
    Professor professor;
    FILE* arquivo;
    FILE* arquivoTurmas;
    int professorEncontrado = 0;
//solicitando a matricula do professor que sera descadastrado
    printf("--- DESCADASTRAR PROFESSOR ---\n");
    printf("Matrícula do professor a ser descadastrado: ");
    scanf("%s", matricula);

    // Verifica se o professor está associado a alguma turma
    arquivoTurmas = fopen("dados/turma/turmas.bin", "rb");
    //abertura do arquivo .bin da turma para verificar se o professor está cadastrado em alguma turma.
    if (arquivoTurmas != NULL) {
        // Verifica se conseguiu abrir o arquivo da turma.
        Turma turma;
        // loop para consultar turmas se existe professor associado a turma.
        while (fread(&turma, sizeof(Turma), 1, arquivoTurmas)) {
             //verificar se a matricula informada é igual a do professor cadastrado.
            if (strcmp(turma.professor.matricula, matricula) == 0) {
                //caso atenda a condição anterior imprimir.
                printf("O professor está associado à turma %s. Não é possível descadastrá-lo!\n", turma.codigo);
                //arquivo é fechado e a função encerrada.
                fclose(arquivoTurmas);
                return;
            }
        }
        fclose(arquivoTurmas);
    }
//se a verificação acima for falsa.
//abrir arquivo professores.bin e realizar leitura.
    arquivo = fopen("dados/professor/professores.bin", "r+b");
    if (arquivo == NULL) {
        //caso não consiga abrir apresentar mensagem.
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    FILE* arquivoTemporario = fopen("dados/professor/professores_temp.bin", "w+b");
    if (arquivoTemporario == NULL) {
        //caso não consiga abrir apresentar mensagem.
        printf("Erro ao abrir o arquivo temporário!\n");
        fclose(arquivo);
        return;
    }
//loop para verificar professores.
    while (fread(&professor, sizeof(Professor), 1, arquivo)) {
        //verificar se a matricula informada é igual a matricula inserida.
        if (strcmp(professor.matricula, matricula) == 0) {
             //se a condição for verdadeira, então o professor já é cadastrado.
            professorEncontrado = 1;
            //se não o professor é escrito no arquivo temporario.
        } else {
            fwrite(&professor, sizeof(Professor), 1, arquivoTemporario);
        }
    }
 //fechando arquivo professores.bin e temp.bin
    fclose(arquivo);
    fclose(arquivoTemporario);
//caso o professor seja encontrado.
    if (professorEncontrado) {
         //removido o professor do professores.bin
        remove("dados/professor/professores.bin");
        //professores.bin é renomeado pra professores_temp.bin
        rename("dados/professor/professores_temp.bin", "dados/professor/professores.bin");
        printf("Professor descadastrado com sucesso!\n");
    } else {
        remove("dados/professor/professores_temp.bin");
        printf("Professor não encontrado!\n");
    }
}


//sistema de impressão de professores sem turma.
void imprimirProfessoresSemTurma() {
 //abrir arquivos de turma.bin e professores.bin
    //declarando os seus ponteiros.
    FILE* arquivoTurmas = fopen("dados/turma/turmas.bin", "rb");
    FILE* arquivoProfessores = fopen("dados/professor/professores.bin", "rb");
//verificando se o arquivo turmas.bin é aberto.
//imprimindo mensagem caso não.
    if (arquivoTurmas == NULL) {
        printf("Não há turmas cadastradas!\n");
        return;
    }
//verificando se o arquivo professores pode abrir.
    if (arquivoProfessores == NULL) {
        printf("Não há professores cadastrados!\n");
        fclose(arquivoTurmas);
        return;
    }
//declarando as variveis.
    Turma turma;
    Professor professor;
    int professorAssociado;

    printf("--- PROFESSORES SEM TURMA ---\n\n");
//loop para verificar para verificar se o professor está associado a alguma turma.
    while (fread(&professor, sizeof(Professor), 1, arquivoProfessores)) {
        fseek(arquivoTurmas, 0, SEEK_SET);
        professorAssociado = 0;
//loop para ler registro de turma do arquivo de turma.comparando a matricula do professor.
        while (fread(&turma, sizeof(Turma), 1, arquivoTurmas)) {
            if (strcmp(professor.matricula, turma.professor.matricula) == 0) {
                professorAssociado = 1;
                break;
            }
        }
//condição para verificar se não está associado. imprimindo informações.
        if (!professorAssociado) {
            printf("Matrícula: %s\n", professor.matricula);
            printf("Nome: %s\n", professor.nome);
            printf("CPF: %s\n", professor.cpf);
            printf("-------------------------------\n");
        }
    }
//fechando arquivo.
    fclose(arquivoTurmas);
    fclose(arquivoProfessores);
}