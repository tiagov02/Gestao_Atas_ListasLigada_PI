//
// Created by Tiago Viana on 04/07/2021.
//

#include "stack.h"

void pop(char stack[][20], int *tos){
    if((*tos)<=0){
        printf("Stack underflow\n");
    }
    else {
        memset(stack[(*tos)-1],'\0',20);
        (*tos)--;
    }
}

void push(char stack[][20], char assinatura[], int *tos){
    if((*tos) >= MAX_ACIONISTAS){
        printf("Stack Overflow\n");
        return;
    }
    strcpy(stack[*tos], assinatura);
    (*tos)++;
}

int top(char stack[][20], int tos,char nomeAssina[]){
    char aux[20]={'\0'};
    if(tos<=0){
        printf("Stack underflow\n");
        return 0;
    }
    else {
        if(strcmp(nomeAssina,stack[tos-1])==0) return 1;
    }
    return 0;
}

void imprimeStack(char stack[][20], int tos){
    int i=0;
    for(i=0;i<tos;i++){
        printf("\n%s",stack[i]);
    }
}



void insereDataHora(int dia[],int mes[], int ano[],int hora[],int minuto[] ,int tos){
    struct tm *data_hora=NULL;
    time_t segs;
    time(&segs);
    data_hora= localtime(&segs);

    dia[tos-1]=data_hora->tm_mday;
    mes[tos-1]=data_hora->tm_mon+1;
    ano[tos-1]=data_hora->tm_year+1900;
    hora[tos-1]=data_hora->tm_hour;
    minuto[tos-1]=data_hora->tm_min;
}

void imprimeNaoAsssinaram(int dia[],int mes[],int ano[],int hora[], int min[], char razao[][100],
                          char stack[][20], int tos){

    int i=0;
    for(i=0;i<tos;i++){
        printf("\n\tNome do acionista: %s",stack[i]);
        printf("\n\tHora: %i:%i",hora[i],min[i]);
        printf("\n\tDia: %i/%i/%i",dia[i],mes[i],ano[i]);
        printf("\n\tRAZÃO porque não assinou: %s",razao[i]);
    }

}

void imprimeAssinaram(int dia[], int mes[],int ano[], int hora[], int min[], char stack[][20], int tos){
    int i=0;
    for(i=0;i<tos;i++){
        printf("\n\tNome: %s",stack[i]);
        printf("\n\tHora: %i:%i",hora[i],min[i]);
        printf("\n\tDIA: %i/%i/%i",dia[i],mes[i],ano[i]);
    }
}

void pushNaoAssinou(char stack[][20],char razao[][100], char assinatura[],char razaoIntrod[], int *tos){
    if((*tos) >= MAX_ACIONISTAS){
        printf("Stack Overflow\n");
        return;
    }
    strcpy(stack[*tos], assinatura);
    strcpy(razao[*tos],razaoIntrod);
    (*tos)++;
}

int verificaSeExiste(char stack[][20], int tos, char nome[]){
    int i=0;
    for(i=0;i<tos;i++){
        if(strcmp(stack[i],nome)==0) return 1;
    }
    return 0;
}