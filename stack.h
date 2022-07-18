//
// Created by Tiago Viana on 04/07/2021.
//

#ifndef TRABPRATICORECURSO_STACK_H
#define TRABPRATICORECURSO_STACK_H

/******************INCLUSÕES******************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gestao_atas.h"
/********************************************/
/*****************FUNÇÕES*******************/
void pop(char stack[][20], int *tos);
void push(char stack[][20], char assinatura[], int *tos);
int top(char stack[][20], int tos,char nomeAssina[]);
void imprimeStack(char stack[][20], int tos);
void insereDataHora(int dia[],int mes[], int ano[],int hora[],int minuto[] ,int tos);
void imprimeNaoAsssinaram(int dia[],int mes[],int ano[],int hora[], int min[], char razao[][100]
        ,char stack[][20], int tos);
void imprimeAssinaram(int dia[], int mes[],int ano[], int hora[], int min[], char stack[][20], int tos);
void pushNaoAssinou(char stack[][20],char razao[][100], char assinatura[],char razaoIntrod[], int *tos);
int verificaSeExiste(char stack[][20], int tos, char nome[]);

/******************************************/

#endif //TRABPRATICORECURSO_STACK_H
