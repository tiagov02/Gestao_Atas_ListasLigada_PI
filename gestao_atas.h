//
// Created by Tiago Viana on 01/07/2021.
//

#ifndef TRABPRATICORECURSO_GESTAO_ATAS_H
#define TRABPRATICORECURSO_GESTAO_ATAS_H
/*************INCLUSÕES*****************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "loginsGestaoUsers.h"
/**************************************/

/**************DEFINES*****************/
#define MAX_ACIONISTAS 50
#define MAX_TEXTO 500
#define MAX_LOCAL 50
#define MAX_NOME 20
#define MAX_RAZAO 100
/*************************************/


/**************STRUCTS***************/
typedef struct ata{
    int nAta;
    int estado;     //1- Em redação/ 2-Para assinatura-->Sem alterações/ 3- Concluida->Sem alterações
    int dia,mes,ano; //data
    char local[MAX_LOCAL];
    char texto[MAX_TEXTO];
    char porAssinar[MAX_ACIONISTAS][MAX_NOME];
    char assinado[MAX_ACIONISTAS][MAX_NOME];
    char naoAssinou[MAX_ACIONISTAS][MAX_NOME];
    char razao[MAX_ACIONISTAS][MAX_RAZAO];
    int tos_porAssinar;
    int tos_assinado;
    int tos_naoAssinou;
    int hora_naoAssinou[MAX_ACIONISTAS], minuto_naoAssinou[MAX_ACIONISTAS];
    int dia_naoAssinou[MAX_ACIONISTAS],mes_naoAssinou[MAX_ACIONISTAS],ano_naoAssinou[MAX_ACIONISTAS];
    int hora_assinado[MAX_ACIONISTAS],min_assinado[MAX_ACIONISTAS];
    int dia_assinado[MAX_ACIONISTAS],mes_assinado[MAX_ACIONISTAS], ano_assinado[MAX_ACIONISTAS];
    char aprovacao[30];
}ATA;

typedef struct elem_ata{
    ATA ata;
    struct elem_ata *prox;
}ELEM_ATA;
/************************************/

/**************FUNÇÕES**************/
ATA introduzAta(int nAta,ELEM_USER *iniLista);
void insereIniLL(ELEM_ATA **iniLista, ATA new_ata);
void writeAtasBin(ELEM_ATA *iniLista);
void importaAtas(ELEM_ATA **iniLista);
void modificaDadosAta(ELEM_ATA *iniLista, int id_pesq);
void pesquisaAtas(ELEM_ATA *iniLista, int id_pesq);
void listaAtasPorEstado(ELEM_ATA *iniLista);
void listarAssinaturasEmFalta(ELEM_ATA *iniLista, int id_pesq);
void imprimeAtas(ELEM_ATA *iniLista);
void pesquisaPorLocal(ELEM_ATA *iniLista, char local_pesq[]);
void printAtasDepois(ELEM_ATA *iniLista,int dia, int mes, int ano);
void ordena_emFalta(ELEM_ATA *iniLista);
void pesquisaNaoAprovaram(ELEM_ATA *iniLista, int id_pesq);
void acionistasOpcoes(ELEM_ATA *iniLista, char nomeAcionista[]);
void verificaEstadoAta(int tos_assinado,int tos_naoassinou,int tos_porAssinar,char aprovacao[], int *estado);
void removeAta(ELEM_ATA **iniLista, int idRemover);
void colocaAtasparaAssinatura(ELEM_ATA *iniLista,int id_pesq);
void indicaAtasPorAssinar(ELEM_ATA *iniLista,char acionistaProcura[]);
void passaAtaFicheiroTxt(ELEM_ATA *iniLista, char nomeFicheiro[],int id_pesq);
void passaCsv(int nAta,ELEM_USER *iniLista,ELEM_ATA **iniAta);
/***********************************/

#endif //TRABPRATICORECURSO_GESTAO_ATAS_H
