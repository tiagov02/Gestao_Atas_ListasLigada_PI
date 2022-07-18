//
// Created by Tiago Viana on 01/07/2021.
//

#include "loginsGestaoUsers.h"

USER inserirNovo(ELEM_USER *iniLista){
    USER new_user;
    int opcao=0;
    do{
        printf("\n\tIntroduza o nome do user que pretende adicionar:\n");
        fflush(stdin);
        fgets(new_user.nome,MAX_STRING,stdin);
    }while(userReservado(iniLista,new_user.nome));
    printf("\n\tIntroduza a pass do user:\n");
    fflush(stdin);
    fgets(new_user.pass,MAX_STRING,stdin);
    while(1){
        printf("\n\tIntroduza o tipo de utiizador: 1 para Admin, 2 para Acionista:\n");
        fflush(stdin);
        scanf("%i",&opcao);
        if(opcao==1) {
            new_user.tipo=1;
            break;
        }
        if(opcao==2){
            new_user.tipo=2;
            break;
        }
    }
    return new_user;
}

void writeUsers(ELEM_USER *iniLista){
    int i=0;
    ELEM_USER *aux=NULL;
    FILE *login=NULL;
    login= fopen("login.dat","wb");
    if(login==NULL){
        printf("\n\tHouve um erro na criação do ficheiro!!!\n");
        exit(-1);
    }
    for(aux=iniLista;aux != NULL; aux=aux->prox){
        fwrite((&(aux->user)), sizeof(USER),1,login);
    }
    fclose(login);
}

void importaUtilizador(ELEM_USER **iniLista) {
    USER new_user;
    FILE *login = NULL;
    login = fopen("login.dat","rb");
    if(login == NULL){
        printf("Erro!\n");
        exit(-1);
    }
    while(fread(&new_user, sizeof(USER),1, login)>0){
        inserirLL_users(iniLista, new_user);
    }
    fclose(login);
}


void inserirLL_users(ELEM_USER **iniLista, USER new_user){
    ELEM_USER *novo=NULL;
    novo=(ELEM_USER *) calloc(1,sizeof(ELEM_USER));
    if(novo==NULL){
        printf("\n\tOcorreu um erro ao guardar na memória!!\n");
        return;
    }
    novo->user=new_user;
    novo->prox=NULL;

    if(*iniLista==NULL) *iniLista=novo;
    else {
        novo->prox = *iniLista;
        *iniLista = novo;
    }
}

int userReservado(ELEM_USER *iniLista, char user[]){
    ELEM_USER *aux=NULL;

    for(aux=iniLista;aux != NULL ; aux=aux->prox){
        if(strcmp(aux->user.nome,user)==0) return 1;
    }
    return 0;
}

int verificaUsersBin(){
    FILE *login=NULL;
    login=fopen("login.dat","rb");
    if(login==NULL) return 1;

    return 0;
}

void primeiroUser(){
    USER new_user;
    FILE *login=NULL;
    login= fopen("login.dat","wb");
    if(login == NULL){
        printf("Erro!\n");
        exit(-1);
    }
    int opcao=0;
    printf("\n\tIntroduza o nome do user que pretende adicionar:\n");
    fflush(stdin);
    fgets(new_user.nome,MAX_STRING,stdin);
    printf("\n\tIntroduza a pass do user:\n");
    fflush(stdin);
    fgets(new_user.pass,MAX_STRING,stdin);
    while(1){
        printf("\n\tIntroduza o tipo de utiizador: 1 para Admin, 2 para Acionista:\n");
        fflush(stdin);
        scanf("%i",&opcao);
        if(opcao==1) {
            new_user.tipo=1;
            break;
        }
        if(opcao==2){
            new_user.tipo=2;
            break;
        }
    }
    fwrite(&new_user, sizeof(USER),1,login);
    fclose(login);
}

int loginAcionistas(ELEM_USER *iniLista, char userIntrod[],char passIntrod[]){
    ELEM_USER *aux=NULL;
    for(aux=iniLista;aux != NULL;aux=aux->prox){
        if(strcmp(userIntrod,aux->user.nome)==0 && strcmp(passIntrod,aux->user.pass)==0){
            if(aux->user.tipo==2){
                printf("\n\tFez login com sucesso\n");
                return 1;
            }
        }
    }
    printf("\n\tLogin sem sucesso!!\n");
    return 0;
}

int loginAdmins(ELEM_USER *iniLista, char userIntrod[],char passIntrod[]){
    ELEM_USER *aux=NULL;
    for(aux=iniLista;aux != NULL;aux=aux->prox){
        if(strcmp(userIntrod,aux->user.nome)==0 && strcmp(passIntrod,aux->user.pass)==0){
            if(aux->user.tipo==1){
                printf("\n\tFez login com sucesso\n");
                return 1;
            }
        }
    }
    printf("\n\tLogin sem sucesso!!\n");
    return 0;
}

void removeUser(ELEM_USER **iniLista, char nomeElimina[]){
    ELEM_USER *aux=*iniLista, *ant=NULL;

    if (*iniLista==NULL){
        printf("\n\tLista não existe\n");
        return;
    }
    while(aux!=NULL && strcmp(aux->user.nome,nomeElimina)!=0) {
        ant=aux;
        aux=aux->prox;
    }
    if(aux==NULL){
        printf("\n\tUtilizador não encontrado!!!\n");
        return;
    }
    if(ant==NULL){
        printf("\n\tA remover utilizador...");
        *iniLista= aux->prox;
        printf("\n\tUtilizador remvido com sucesso!!\n");
    }
    else{
        printf("\n\tA remover utilizador...");
        ant->prox=aux->prox;
        printf("\n\tUtilizador remvido com sucesso!!\n");
    }
    free(aux);
}

void modificaDados(ELEM_USER *iniLista, char nomeModifica[]){
    ELEM_USER *aux=NULL;
    char nomeNovo[MAX_STRING], passeNova[MAX_STRING];
    int opcao=0,tipoNovo=0,cont=0;
    for(aux=iniLista; aux != NULL; aux=aux->prox){
        if(strcmp(nomeModifica,aux->user.nome)==0){
            printf("\n\tDados do utilizador que pretende modificar:");
            printf("\nNome: %s",aux->user.nome);
            printf("\nPASSE: %s", aux->user.pass);
            printf("\nTipo: %i",aux->user.tipo);
            printf("\n\n\n");
            cont++;
            while(1){
                printf("\n\tSelecione uma das opções\n");
                printf("\n\t(1)- Modificar o user");
                printf("\n\t(2)- Modificar o tipo de user");
                printf("\n\t(3)- Modificar a pass do user");
                printf("\n\t(4)- Nenhum deles-sair");
                printf("\n\tIntroduza a sua opção");
                fflush(stdin);
                scanf("%i",&opcao);
                if(opcao==1 || opcao==2 || opcao==3) break;
                if(opcao==4) return;
            }

            switch (opcao) {
                case 1:{
                    printf("User antigo %s",aux->user.nome);
                    do{
                        printf("\n\tIntroduza o novo user\n");
                        fflush(stdin);
                        fgets(nomeNovo,MAX_STRING,stdin);
                    }while(userReservado(iniLista,nomeNovo)!=0);
                    strcpy(aux->user.nome,nomeNovo);
                    printf("\n\tModificado com sucesso!");
                    break;
                }
                case 2:{
                    printf("\n\tIntroduza a nova passe:\n");
                    fflush(stdin);
                    fgets(aux->user.pass,MAX_STRING,stdin);
                    printf("\n\tModificado com sucesso!");
                    break;
                }
                case 3:{
                    while(1){
                        printf("\n\t(1)- Para administrador");
                        printf("\n\t(2)- Para acionista");
                        fflush(stdin);
                        scanf("%i",&tipoNovo);
                        if(tipoNovo==1){
                            aux->user.tipo=1;
                            printf("\n\tModificado com sucesso!");
                            break;
                        }
                        if(tipoNovo==2){
                            aux->user.tipo=2;
                            printf("\n\tModificado com sucesso!");
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
    if(cont==0){
        printf("\n\tO utilizador não existe\n");
        return;
    }
}

void consultaDados(ELEM_USER *iniLista, char nomeConsulta[]){
    ELEM_USER *aux=NULL;
    int cont=0;
    for(aux=iniLista; aux != NULL; aux=aux->prox){
        if(strcmp(nomeConsulta,aux->user.nome)==0) {
            printf("\n\tDados do utilizador que pretende consultar:");
            printf("\nNome: %s", aux->user.nome);
            printf("\nPASSE: %s", aux->user.pass);
            printf("\nTipo: %i", aux->user.tipo);
            printf("\n\n\n");
            cont ++;
        }
    }
    if(cont==0) printf("\n\tO nome que pretende consultar não existe");
}


void listaUsers(ELEM_USER *iniLista){
    ELEM_USER *aux=NULL;
    for(aux=iniLista; aux != NULL; aux=aux->prox){
        printf("\nNome: %s",aux->user.nome);
        printf("\nPASSE: %s", aux->user.pass);
        printf("\nTipo: %i",aux->user.tipo);
    }
}

int verificaAcionistas(ELEM_USER *iniLista,char userIntrod[]){
    ELEM_USER *aux=NULL;
    for(aux=iniLista;aux != NULL;aux=aux->prox){
        if(strcmp(userIntrod,aux->user.nome)==0){
            if(aux->user.tipo==2){
                return 1;
            }
        }
    }
    return 0;
}
