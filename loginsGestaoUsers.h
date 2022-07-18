//
// Created by Tiago Viana on 01/07/2021.
//

#ifndef TRABPRATICORECURSO_LOGINSGESTAOUSERS_H
#define TRABPRATICORECURSO_LOGINSGESTAOUSERS_H

/*********INCLUDES**********/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/***************************/

/*********DEFINES*************/
#define MAX_STRING 20
/****************************/

/*********STRUCTS**********/
typedef struct{
    char nome[MAX_STRING], pass[MAX_STRING];
    int tipo;   //1-Administrador / 2-Acionista
}USER;

typedef struct elem_user{
    USER user;
    struct elem_user *prox;
}ELEM_USER;

/*************************/

/*********FUNÇÕES********/
USER inserirNovo(ELEM_USER *iniLista);
void writeUsers(ELEM_USER *iniLista);
void importaUtilizador(ELEM_USER **iniLista);
void inserirLL_users(ELEM_USER **iniLista, USER new_user);
int userReservado(ELEM_USER *iniLista, char user[]);
int verificaUsersBin();
void primeiroUser();
int loginAcionistas(ELEM_USER *iniLista, char userIntrod[],char passIntrod[]);
int loginAdmins(ELEM_USER *iniLista, char userIntrod[],char passIntrod[]);
void removeUser(ELEM_USER **iniLista, char nomeElimina[]);
void modificaDados(ELEM_USER *iniLista, char nomeModifica[]);
void consultaDados(ELEM_USER *iniLista, char nomeConsulta[]);
void listaUsers(ELEM_USER *iniLista);
int verificaAcionistas(ELEM_USER *iniLista,char userIntrod[]);
/************************/

#endif //TRABPRATICORECURSO_LOGINSGESTAOUSERS_H
