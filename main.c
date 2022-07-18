
/*********FICHEIRO INCLUSÕES************/
#include "inclusoes.h"
/**************************************/

void gestaoAtas(ELEM_ATA **iniAta, ELEM_USER **iniUser){
    int opcao1=0;
    ATA new_ata;
    int id_pesq=0,diaPesq=0,mesPesq=0,anoPesq=0;
    char localPesq[MAX_LOCAL],acionistaPesq[MAX_STRING],nomeFicheiro[50];
    do{
        opcao1=menuAdmin2();
        switch (opcao1) {
            case 1:{
                if((*iniAta)==NULL){
                    new_ata= introduzAta(0,*iniUser);
                    insereIniLL(iniAta,new_ata);
                    writeAtasBin((*iniAta));
                    break;
                }
                else{
                    new_ata= introduzAta((*iniAta)->ata.nAta,(*iniUser));
                    insereIniLL(iniAta,new_ata);
                    writeAtasBin((*iniAta));
                    break;
                }
                break;
            }
            case 2:{
                printf("\n\tQual o id da ata que pretende pesquisar?  ");
                fflush(stdin);
                scanf("%i",&id_pesq);
                pesquisaAtas((*iniAta),id_pesq);
                id_pesq=0;
                break;
            }
            case 3:{
                listaAtasPorEstado((*iniAta));
                break;
            }
            case 4:{
                printf("\n\tDe qual das atas quer ver se os acionistas ja assinaram?\n");
                fflush(stdin);
                scanf("%i",&id_pesq);
                listarAssinaturasEmFalta((*iniAta),id_pesq);
                break;
            }
            case 5:{
                printf("\n\tIntroduza o dia\n");
                fflush(stdin);
                scanf("%i",&diaPesq);
                printf("\n\tIntroduza o mês:\n");
                fflush(stdin);
                scanf("%i",&mesPesq);
                printf("\n\tIntroduza o ano:\n");
                fflush(stdin);
                scanf("%i",&anoPesq);
                printAtasDepois((*iniAta),diaPesq,mesPesq,anoPesq);
                break;
            }
            case 6:{
                printf("\n\tQual o local que pretende ver as atas?\n");
                fflush(stdin);
                fgets(localPesq,MAX_LOCAL,stdin);
                pesquisaPorLocal((*iniAta),localPesq);
                break;
            }
            case 7:{
                printf("\n\tDe qual das atas quer ver se quais os acionistas que se recusaram a assinar?\n");
                fflush(stdin);
                scanf("%i",&id_pesq);
                pesquisaNaoAprovaram((*iniAta),id_pesq);
                break;
            }
            case 8:{
                printf("\n\tIntroduza qual o acionista que quer consultar todas as atas em que falta assinar:\n");
                fflush(stdin);
                fgets(acionistaPesq,MAX_STRING,stdin);
                indicaAtasPorAssinar((*iniAta),acionistaPesq);
                break;
            }
            case 9:{
                printf("\n\tAtas ordenadas por numero de assinaturas em Falta:\n");
                ordena_emFalta((*iniAta));
                break;
            }
            case 10:{
                printf("\n\tIntroduza o id da ata que quer modificar\n");
                fflush(stdin);
                scanf("%i",&id_pesq);
                modificaDadosAta((*iniAta),id_pesq);
                break;
            }
            case 11:{
                printf("\n\tQual o id da ata que pretende eliminar?\n");
                fflush(stdin);
                scanf("%i",&id_pesq);
                colocaAtasparaAssinatura((*iniAta),id_pesq);
                break;
            }
            case 12:{
                printf("Introduza o id da ata que quer remover:\n");
                fflush(stdin);
                scanf("%i",&id_pesq);
                removeAta(iniAta,id_pesq);
                break;
            }
            case 13:{
                printf("\n\tIntroduza o id da ata que quer passar para ficheiro de texto:\n");
                fflush(stdin);
                scanf("%i",&id_pesq);
                printf("\n\tIntroduza o nome do ficheiro que quer: ");
                fflush(stdin);
                gets(nomeFicheiro);
                passaAtaFicheiroTxt((*iniAta),nomeFicheiro,id_pesq);
            }
            case 14:{
                imprimeAtas((*iniAta));
            }
            case 15:{
                if((*iniAta)==NULL){
                    passaCsv(0,(*iniUser),iniAta);
                }
                else{
                    passaCsv((*iniAta)->ata.nAta,(*iniUser),iniAta);
                }
                break;
            }
            default:{break;}
        }
    }while((opcao1 != 0));
}

int main(int argc, const char *argv[]) {
    int opcaoInicial=0,opcaoAdm1=0,opcaoAdm2=0;
    USER new_user;
    ELEM_USER *iniUser=NULL;
    ELEM_ATA *iniAta=NULL;
    int sucesso=0,sucessoAcionistas=0;
    char loginIntrod[MAX_STRING], passIntrod[MAX_STRING], nomeModifca[MAX_STRING],nomeConsulta[MAX_STRING];
    if(verificaUsersBin()) {
        printf("\n\tNão existem utilizadores introduzidos!!!!\n");
        printf("\n\tA redirecionar para a criação de users\n\n");
        primeiroUser();
    }
    importaUtilizador(&iniUser);
    importaAtas(&iniAta);
    //imprimeAtas(iniAta);
    do{
        opcaoInicial=menuInicial();

        switch (opcaoInicial) {
            case 1:{
                printf("\n\tIntroduza o seu utilizador:\n");
                fflush(stdin);
                fgets(loginIntrod,MAX_STRING,stdin);
                printf("\n\nIntroduza a sua pass:\n");
                fflush(stdin);
                fgets(passIntrod,MAX_STRING,stdin);
                sucesso=loginAdmins(iniUser,loginIntrod,passIntrod);
                if(sucesso==0){
                    printf("\n\tA redirecionar para o menu anterior\n");
                    break;
                }
                if(sucesso==1){
                    do{
                        opcaoAdm1=menuAdmin();
                        switch (opcaoAdm1) {
                            case 1:{
                                opcaoAdm2=menuAdmin1();
                                switch (opcaoAdm2) {
                                    case 1:{
                                        new_user=inserirNovo(iniUser);
                                        inserirLL_users(&iniUser,new_user);
                                        writeUsers(iniUser);
                                        break;
                                    }
                                    case 2:{
                                        printf("\n\tQual é o user que pretende modificar?\n");
                                        fflush(stdin);
                                        fgets(nomeModifca,MAX_STRING,stdin);
                                        modificaDados(iniUser,nomeModifca);
                                        writeUsers(iniUser);
                                        break;
                                    }
                                    case 3:{
                                        printf("\n\tQual é o user que pretende consultar?\n");
                                        fflush(stdin);
                                        fgets(nomeConsulta,MAX_STRING,stdin);
                                        consultaDados(iniUser,nomeConsulta);
                                        break;
                                    }
                                    case 4:{
                                        printf("\n\tQual é o user que pretende modificar?\n");
                                        fflush(stdin);
                                        fgets(nomeModifca,MAX_STRING,stdin);
                                        removeUser(&iniUser,nomeModifca);
                                        writeUsers(iniUser);
                                        break;
                                    }
                                    case 5:{
                                        listaUsers(iniUser);
                                        break;
                                    }
                                    default:{break;}
                                }
                                break;
                            }
                            case 2:{
                                gestaoAtas(&iniAta,&iniUser);
                                break;
                            }
                            default:{break;}
                        }
                    } while (opcaoAdm1 != 0);
                }
                break;
            }
            case 2:{
                printf("\n\tIntroduza o seu username:\n");
                fflush(stdin);
                fgets(loginIntrod,MAX_STRING,stdin);
                printf("\n\tIntroduza a sua passe:\n");
                fflush(stdin);
                fgets(passIntrod,MAX_STRING,stdin);
                sucessoAcionistas= loginAcionistas(iniUser,loginIntrod,passIntrod);
                if(sucessoAcionistas==0){
                    printf("\n\tA redirecionar para o menu anterior\n");
                    break;
                }
                if(sucessoAcionistas==1){
                    printf("\n\t AQUI ASSINA AS SUAS ATAS");
                    acionistasOpcoes(iniAta,loginIntrod);
                }
                break;
            }
        }
    }while(opcaoInicial != 0);
    return 0;
}