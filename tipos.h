#ifndef _TIPOS_H
#define _TIPOS_H

typedef struct {
    char logradouro[100];
    char bairro[50];
    char cidade[50];
    char estado[50];
    char numero[10];
} Endereco;

typedef struct {
    char matricula[10];
    char cpf[12];
    char nome[50];
    Endereco endereco;
} Aluno;

typedef struct {
    char matricula[10];
    char cpf[12];
    char nome[50];
    Endereco endereco;
} Professor;

typedef struct {
    char codigo[10];
    char nome[50];
    Professor professor;
    Aluno alunos[40];
    int numAlunos;
    float media;
} Turma;

#endif