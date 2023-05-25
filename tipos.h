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
    char CPF[13];
    char nome[100];
    Endereco endereco;
} Aluno;

typedef struct {
    char matricula[10];
    char cpf[13];
    char nome[100];
    Endereco endereco;
} Professor;

#endif