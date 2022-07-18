//
// Created by Tiago Viana on 30/06/2021.
//

#include "menus.h"

int menuInicial(){
    int opcao=0;
    printf("\n\t**************LOGIN*****************");
    printf("\n\t(1)- Sou um Administrador");
    printf("\n\t(2)- Sou um Acionista");
    printf("\n\tIntroduza a sua opção\n");
    scanf("%i",&opcao);
    return opcao;
}

int menuAdmin(){
    int opcao=0;
    printf("\n\t(1)- Gerir os utilizadores");
    printf("\n\t(2)- Gerir as atas");
    printf("\n\tIntroduza a sua opção\n");
    scanf("%i",&opcao);
    return opcao;
}

int menuAdmin1(){
    int opcao = 0;
    printf("\n********MENU GESTAO USERS************");
    printf("\n\t(1)-Introduzir um novo utilizador");
    printf("\n\t(2)-Modificar os dados de um utilizador");
    printf("\n\t(3)-Consultar os dados de um utilizador");
    printf("\n\t(4)- Eliminar um utilizador");
    printf("\n\t(5)-Listar todos os users");
    printf("\n\tIntroduza a sua opção:\n");
    scanf("%i", &opcao);
    return opcao;
}

int menuAdmin2(){
    int opcao=0;
    printf("\n****************************GESTAO ATAS******************************");
    printf("\n\t(1)- Introduzir nova ata");
    printf("\n\t(2)- Pesquisar uma ata");
    printf("\n\t(3)- Listar as atas por estado");
    printf("\n\t(4)- Listar as assinaturas em falta numa determinada ata");
    printf("\n\t(5)- Listar as atas que tenham ocorrido apos uma data");
    printf("\n\t(6)- Pesquisar todas as atas de um local da assembleia");
    printf("\n\t(7)- Listar os acionistas cujos não aprovaram uma ata, dado o id da ata");
    printf("\n\t(8)- Listar as atas que faltam ser assinadas de um determinado acionista");
    printf("\n\t(9)- Listar todas as atas ordenadas por numero de assinaturas em falta");//
    printf("\n\t(10)- Alterar dados de atas, dado o seu id");
    printf("\n\t(11)- Colocar uma ata para assinatura dado o seu id");
    printf("\n\t(12)- Eliminar uma ata dado o seu id");
    printf("\n\t(13)-Passar uma ata para ficheiro de texto");
    printf("\n\t(14)- Listar todas as atas");
    printf("\n\t(15)-Importar atas de um ficheiro csv");
    printf("\n\tOutra opção qualquer para sair");
    printf("\n\tIntroduza a sua opção:\n");
    scanf("%i",&opcao);
    return opcao;
}
