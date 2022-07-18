//
// Created by Tiago Viana on 01/07/2021.
//

#include "gestao_atas.h"

ATA introduzAta(int nAta,ELEM_USER *iniLista){
    ATA new_ata;
    int nAcionistas=0,i=0,opcao=0;
    char nomeAcionista[MAX_NOME];
    new_ata.nAta=nAta+1;
    new_ata.tos_porAssinar=0;
    new_ata.tos_assinado=0;
    new_ata.tos_naoAssinou=0;
    printf("\n\tIntroduza o dia da ata:\n");
    fflush(stdin);
    scanf("%i",&new_ata.dia);
    printf("\n\tIntroduza o mês da ata:\n");
    fflush(stdin);
    scanf("%i",&new_ata.mes);
    printf("\n\tIntroduza o ano da ata:\n");
    fflush(stdin);
    scanf("%i",&new_ata.ano);
    printf("\n\tIntroduza o local da assembleia:\n");
    fflush(stdin);
    fgets(new_ata.local,MAX_LOCAL,stdin);
    printf("\n\tIntroduza o texto da ata:\n");
    fflush(stdin);
    fgets(new_ata.texto,MAX_TEXTO,stdin);
    do{
        printf("\n\tIntroduza o numero de acionistas presentes nesta assembleia:\n");
        fflush(stdin);
        scanf("%i",&nAcionistas);
    }while(nAcionistas>MAX_ACIONISTAS);
    printf("\n\tIntroduza os nomes dos acionistas por ordem de chegada:\n");
    for(i=0;i<nAcionistas;i++){
        while(1){
            printf("\n\tIntroduza o nome do %iº acionista: ",i+1);
            fflush(stdin);
            fgets(nomeAcionista,MAX_STRING,stdin);
            if(verificaAcionistas(iniLista,nomeAcionista)) break;
        }
        push(new_ata.porAssinar,nomeAcionista,&new_ata.tos_porAssinar);
    }
    printf("\n\tPretende colocar esta ata disponível para assinatura, sabendo que não a poderá editar?");
    printf("\n\tSe sim pressione a tecla 1, se não presione qualquer outra tecla\n");
    fflush(stdin);
    scanf("%i",&opcao);
    if(opcao==1) new_ata.estado=2;
    else new_ata.estado=1;
    return new_ata;
}

void insereIniLL(ELEM_ATA **iniLista, ATA new_ata){
    ELEM_ATA *novo=NULL;
    novo=(ELEM_ATA *) calloc(1, sizeof(ELEM_ATA));
    if(novo==NULL){
        printf("\n\tAtingiu o Limite de memória\n");
        exit(-1);
    }
    novo->ata=new_ata;
    novo->prox=NULL;
    if(*iniLista==NULL) *iniLista=novo;
    else {
        novo->prox = *iniLista;
        *iniLista = novo;
    }
}

void writeAtasBin(ELEM_ATA *iniLista){
    ELEM_ATA *aux=NULL;
    FILE *atas=NULL;
    atas=fopen("atas.DAT","wb");
    if(atas==NULL){
        printf("\n\tOcorreu um erro no ficheiro!!\n");
        exit(-1);
    }
    for(aux=iniLista;aux != NULL; aux=aux->prox){
        fwrite(&(aux->ata),sizeof(ATA),1,atas);
    }
    fclose(atas);
}

void importaAtas(ELEM_ATA **iniLista){
    ATA new_ata;
    FILE *atas=NULL;
    atas=fopen("atas.DAT","rb");
    if(atas==NULL){
        printf("\n\tNão existem atas a importar");
        return;
    }
    while(fread(&new_ata, sizeof(ATA),1,atas)>0){
        insereIniLL(iniLista,new_ata);
    }
    fclose(atas);
}

void modificaDadosAta(ELEM_ATA *iniLista, int id_pesq){
    ELEM_ATA *aux=NULL;
    int cont=0,i=0,opcao=0;

    if(iniLista==NULL){
        printf("\n\tNÃO EXISTEM ATAS");
        return;
    }
    for(aux=iniLista;aux != NULL; aux=aux->prox){
        if(id_pesq==aux->ata.nAta){
            printf("\nID DA ATA: %i",aux->ata.nAta);
            printf("\nData da ata %i/%i/%i",aux->ata.dia,aux->ata.mes,aux->ata.ano);
            printf("\nLOCAL DA ASSEMBLEIA %s",aux->ata.local);
            printf("\nTEXTO DA ATA:\n%s",aux->ata.texto);
            if(aux->ata.estado==1) printf("\nESTADO: EM REDAÇÃO");
            if(aux->ata.estado==2) printf("\nESTADO: PARA ASSINATURA");
            if(aux->ata.estado==3) {
                printf("\nESTADO: CONCLUÍDA");
                printf("\nEstado de aprovação: %s",aux->ata.aprovacao);
            }
            printf("\nAcionistas que faltam assinar:\n");
            imprimeStack(aux->ata.porAssinar,aux->ata.tos_porAssinar);
            printf("\nAcionistas que já assinaram:\n");
            imprimeAssinaram(aux->ata.dia_assinado,aux->ata.mes_assinado,aux->ata.ano_assinado,aux->ata.hora_assinado,
                             aux->ata.min_assinado,aux->ata.assinado,aux->ata.tos_assinado);
            printf("\nAcionistas que se recusaram a assinar:\n");
            imprimeNaoAsssinaram(aux->ata.dia_naoAssinou,aux->ata.mes_naoAssinou,aux->ata.ano_naoAssinou,
                                 aux->ata.hora_naoAssinou,aux->ata.minuto_naoAssinou,aux->ata.razao,aux->ata.naoAssinou,
                                 aux->ata.tos_naoAssinou);
            cont++;

            printf("\n\tQual dos dados pretende modificar?\n");
            printf("\n\t(1)-Texto da ata");
            printf("\n\t(2)-Local da assembleia");
            printf("\n\t(3)-Data da ata");
            printf("\n\tQualquer opção para sair");
            printf("\n\tIntroduza a sua opção: \n");
            fflush(stdin);
            scanf("%i",&opcao);

            if(opcao==1){
                printf("\n\tIntroduza o novo texto da ata");
                fflush(stdin);
                fgets(aux->ata.texto,MAX_TEXTO,stdin);
                printf("\n\tMODIFICOU A ATA COM SUCESSO!!!!");
                writeAtasBin(iniLista);
            }
            if(opcao==2){
                printf("\n\tIntroduza o local da ata");
                fflush(stdin);
                fgets(aux->ata.local,MAX_LOCAL,stdin);
                printf("\n\tMODIFICOU A ATA COM SUCESSO!!!!");
                writeAtasBin(iniLista);
            }
            if(opcao==3){
                printf("\n\tIntroduza o novo dia da ata\n");
                fflush(stdin);
                scanf("%i",&aux->ata.dia);
                printf("\n\tIntroduza o novo mês da ata\n");
                fflush(stdin);
                scanf("%i",&aux->ata.mes);
                printf("\n\tIntroduza o novo ano da ata:\n");
                fflush(stdin);
                scanf("%i",&aux->ata.ano);
                printf("\n\tMODIFICOU A ATA COM SUCESSO!!!!");
                writeAtasBin(iniLista);
            }
        }
    }
    if(cont==0){
        printf("\n\tNão foram encontradas atas com o id introduzido!!\n");
        return;
    }
}

void pesquisaAtas(ELEM_ATA *iniLista, int id_pesq){
    ELEM_ATA *aux=NULL;
    int cont=0,i=0;

    if(iniLista==NULL){
        printf("\n\tNÃO EXISTEM ATAS");
        return;
    }
    for(aux=iniLista;aux != NULL; aux=aux->prox){
        if(id_pesq==aux->ata.nAta){
            printf("\nID DA ATA: %i",aux->ata.nAta);
            printf("\nData da ata %i/%i/%i",aux->ata.dia,aux->ata.mes,aux->ata.ano);
            printf("\nLOCAL DA ASSEMBLEIA %s",aux->ata.local);
            printf("\nTEXTO DA ATA:\n%s",aux->ata.texto);
            if(aux->ata.estado==1) printf("\nESTADO: EM REDAÇÃO");
            if(aux->ata.estado==2) printf("\nESTADO: PARA ASSINATURA");
            if(aux->ata.estado==3) {
                printf("\nESTADO: CONCLUÍDA");
                printf("\nEstado de aprovação: %s",aux->ata.aprovacao);
            }
            printf("\nAcionistas que faltam assinar:\n");
            imprimeStack(aux->ata.porAssinar,aux->ata.tos_porAssinar);
            printf("\nAcionistas que já assinaram:\n");
            imprimeAssinaram(aux->ata.dia_assinado,aux->ata.mes_assinado,aux->ata.ano_assinado,aux->ata.hora_assinado,
                             aux->ata.min_assinado,aux->ata.assinado,aux->ata.tos_assinado);
            printf("\nAcionistas que se recusaram a assinar:\n");
            imprimeNaoAsssinaram(aux->ata.dia_naoAssinou,aux->ata.mes_naoAssinou,aux->ata.ano_naoAssinou,
                                 aux->ata.hora_naoAssinou,aux->ata.minuto_naoAssinou,aux->ata.razao,aux->ata.naoAssinou,
                                 aux->ata.tos_naoAssinou);
            cont++;
        }
    }
    if(cont==0){
        printf("\n\tNão foram encontradas atas com o id introduzido!!\n");
        return;
    }
}

void listaAtasPorEstado(ELEM_ATA *iniLista){
    ELEM_ATA *aux=NULL;
    if(iniLista==NULL){
        printf("\n\tNÃO EXISTEM ATAS");
        return;
    }
    for(aux=iniLista;aux != NULL ; aux=aux->prox){
        printf("\n\tATAS COM O ESTADO EM REDAÇÃO\n\n");
        if(aux->ata.estado==1){
            printf("\nID DA ATA: %i",aux->ata.nAta);
            printf("\nData da ata %i/%i/%i",aux->ata.dia,aux->ata.mes,aux->ata.ano);
            printf("\nLOCAL DA ASSEMBLEIA %s",aux->ata.local);
            printf("\nTEXTO DA ATA:\n%s",aux->ata.texto);
            if(aux->ata.estado==1) printf("\nESTADO: EM REDAÇÃO");
            if(aux->ata.estado==2) printf("\nESTADO: PARA ASSINATURA");
            if(aux->ata.estado==3) {
                printf("\nESTADO: CONCLUÍDA");
                printf("\nEstado de aprovação: %s",aux->ata.aprovacao);
            }
            printf("\nAcionistas que faltam assinar:\n");
            imprimeStack(aux->ata.porAssinar,aux->ata.tos_porAssinar);
            printf("\nAcionistas que já assinaram:\n");
            imprimeAssinaram(aux->ata.dia_assinado,aux->ata.mes_assinado,aux->ata.ano_assinado,aux->ata.hora_assinado,
                             aux->ata.min_assinado,aux->ata.assinado,aux->ata.tos_assinado);
            printf("\nAcionistas que se recusaram a assinar:\n");
            imprimeNaoAsssinaram(aux->ata.dia_naoAssinou,aux->ata.mes_naoAssinou,aux->ata.ano_naoAssinou,
                                 aux->ata.hora_naoAssinou,aux->ata.minuto_naoAssinou,aux->ata.razao,aux->ata.naoAssinou,
                                 aux->ata.tos_naoAssinou);
        }
    }
    aux=NULL;
    for(aux=iniLista;aux != NULL ; aux=aux->prox){
        printf("\n\tATAS COM O ESTADO PARA ASSINATURA");
        if(aux->ata.estado==2){
            printf("\nID DA ATA: %i",aux->ata.nAta);
            printf("\nData da ata %i/%i/%i",aux->ata.dia,aux->ata.mes,aux->ata.ano);
            printf("\nLOCAL DA ASSEMBLEIA %s",aux->ata.local);
            printf("\nTEXTO DA ATA:\n%s",aux->ata.texto);
            if(aux->ata.estado==1) printf("\nESTADO: EM REDAÇÃO");
            if(aux->ata.estado==2) printf("\nESTADO: PARA ASSINATURA");
            if(aux->ata.estado==3) {
                printf("\nESTADO: CONCLUÍDA");
                printf("\nEstado de aprovação: %s",aux->ata.aprovacao);
            }
            printf("\nAcionistas que faltam assinar:\n");
            imprimeStack(aux->ata.porAssinar,aux->ata.tos_porAssinar);
            printf("\nAcionistas que já assinaram:\n");
            imprimeAssinaram(aux->ata.dia_assinado,aux->ata.mes_assinado,aux->ata.ano_assinado,aux->ata.hora_assinado,
                             aux->ata.min_assinado,aux->ata.assinado,aux->ata.tos_assinado);
            printf("\nAcionistas que se recusaram a assinar:\n");
            imprimeNaoAsssinaram(aux->ata.dia_naoAssinou,aux->ata.mes_naoAssinou,aux->ata.ano_naoAssinou,
                                 aux->ata.hora_naoAssinou,aux->ata.minuto_naoAssinou,aux->ata.razao,aux->ata.naoAssinou,
                                 aux->ata.tos_naoAssinou);
        }
    }
    aux=NULL;
    for(aux=iniLista;aux != NULL ; aux=aux->prox){
        printf("\nATAS COM O ESTADO CONCLUIDA");
        if(aux->ata.estado==3){
            printf("\nID DA ATA: %i",aux->ata.nAta);
            printf("\nData da ata %i/%i/%i",aux->ata.dia,aux->ata.mes,aux->ata.ano);
            printf("\nLOCAL DA ASSEMBLEIA %s",aux->ata.local);
            printf("\nTEXTO DA ATA:\n%s",aux->ata.texto);
            if(aux->ata.estado==1) printf("\nESTADO: EM REDAÇÃO");
            if(aux->ata.estado==2) printf("\nESTADO: PARA ASSINATURA");
            if(aux->ata.estado==3) {
                printf("\nESTADO: CONCLUÍDA");
                printf("\nEstado de aprovação: %s",aux->ata.aprovacao);
            }
            printf("\nAcionistas que faltam assinar:\n");
            imprimeStack(aux->ata.porAssinar,aux->ata.tos_porAssinar);
            printf("\nAcionistas que já assinaram:\n");
            imprimeAssinaram(aux->ata.dia_assinado,aux->ata.mes_assinado,aux->ata.ano_assinado,aux->ata.hora_assinado,
                             aux->ata.min_assinado,aux->ata.assinado,aux->ata.tos_assinado);
            printf("\nAcionistas que se recusaram a assinar:\n");//VER-->Requesito de ter o dia/hora da assinatura
            imprimeNaoAsssinaram(aux->ata.dia_naoAssinou,aux->ata.mes_naoAssinou,aux->ata.ano_naoAssinou,
                                 aux->ata.hora_naoAssinou,aux->ata.minuto_naoAssinou,aux->ata.razao,aux->ata.naoAssinou,
                                 aux->ata.tos_naoAssinou);
        }
    }
}

void listarAssinaturasEmFalta(ELEM_ATA *iniLista, int id_pesq){
    ELEM_ATA *aux=NULL;
    if(iniLista==NULL){
        printf("\n\tNÃO EXISTEM ATAS");
        return;
    }
    printf("\nAs assinaturas em falta na ata são:");
    for(aux=iniLista;aux != NULL ; aux=aux->prox){
        if(id_pesq==aux->ata.nAta){
            imprimeStack((aux->ata.porAssinar),(aux->ata.tos_porAssinar));
        }
    }
}

void imprimeAtas(ELEM_ATA *iniLista){
    ELEM_ATA *aux=NULL;
    int cont=0;
    if(iniLista==NULL){
        printf("\n\tNÃO EXISTEM ATAS");
        return;
    }
    for(aux=iniLista;aux != NULL; aux=aux->prox){
        printf("\nID DA ATA: %i",aux->ata.nAta);
        printf("\nData da ata %i/%i/%i",aux->ata.dia,aux->ata.mes,aux->ata.ano);
        printf("\nLOCAL DA ASSEMBLEIA %s",aux->ata.local);
        printf("\nTEXTO DA ATA:\n%s",aux->ata.texto);
        if(aux->ata.estado==1) printf("\nESTADO: EM REDAÇÃO");
        if(aux->ata.estado==2) printf("\nESTADO: PARA ASSINATURA");
        if(aux->ata.estado==3) {
            printf("\nESTADO: CONCLUÍDA");
            printf("\nEstado de aprovação: %s",aux->ata.aprovacao);
        }
        printf("\nAcionistas que faltam assinar:\n");
        imprimeStack(aux->ata.porAssinar,aux->ata.tos_porAssinar);
        printf("\nAcionistas que já assinaram:\n");
        imprimeAssinaram(aux->ata.dia_assinado,aux->ata.mes_assinado,aux->ata.ano_assinado,aux->ata.hora_assinado,
                         aux->ata.min_assinado,aux->ata.assinado,aux->ata.tos_assinado);
        printf("\nAcionistas que se recusaram a assinar:\n");
        imprimeNaoAsssinaram(aux->ata.dia_naoAssinou,aux->ata.mes_naoAssinou,aux->ata.ano_naoAssinou,
                             aux->ata.hora_naoAssinou,aux->ata.minuto_naoAssinou,aux->ata.razao,aux->ata.naoAssinou,
                             aux->ata.tos_naoAssinou);
        }
}

void pesquisaPorLocal(ELEM_ATA *iniLista, char local_pesq[]){
    ELEM_ATA *aux=NULL;
    int cont=0;
    if(iniLista==NULL){
        printf("\n\tNÃO EXISTEM ATAS");
        return;
    }
    for(aux=iniLista;aux != NULL; aux=aux->prox){
        if(strcmp(local_pesq,aux->ata.local)==0){
            printf("\nID DA ATA: %i",aux->ata.nAta);
            printf("\nData da ata %i/%i/%i",aux->ata.dia,aux->ata.mes,aux->ata.ano);
            printf("\nLOCAL DA ASSEMBLEIA %s",aux->ata.local);
            printf("\nTEXTO DA ATA:\n%s",aux->ata.texto);
            if(aux->ata.estado==1) printf("\nESTADO: EM REDAÇÃO");
            if(aux->ata.estado==2) printf("\nESTADO: PARA ASSINATURA");
            if(aux->ata.estado==3) {
                printf("\nESTADO: CONCLUÍDA");
                printf("\nEstado de aprovação: %s",aux->ata.aprovacao);
            }
            printf("\nAcionistas que faltam assinar:\n");
            imprimeStack(aux->ata.porAssinar,aux->ata.tos_porAssinar);
            printf("\nAcionistas que já assinaram:\n");
            imprimeAssinaram(aux->ata.dia_assinado,aux->ata.mes_assinado,aux->ata.ano_assinado,aux->ata.hora_assinado,
                             aux->ata.min_assinado,aux->ata.assinado,aux->ata.tos_assinado);
            printf("\nAcionistas que se recusaram a assinar:\n");
            imprimeNaoAsssinaram(aux->ata.dia_naoAssinou,aux->ata.mes_naoAssinou,aux->ata.ano_naoAssinou,
                                 aux->ata.hora_naoAssinou,aux->ata.minuto_naoAssinou,aux->ata.razao,aux->ata.naoAssinou,
                                 aux->ata.tos_naoAssinou);
            cont++;
        }
    }
    if(cont==0){
        printf("\n\tNão foram encontradas atas com o id introduzido!!\n");
        return;
    }
}

void printAtasDepois(ELEM_ATA *iniLista,int dia, int mes, int ano){
    ELEM_ATA *aux=NULL;
    if(iniLista==NULL){
        printf("\n\tNÃO EXISTEM ATAS");
        return;
    }
    for(aux=iniLista;aux != NULL; aux=aux->prox){
        if(aux->ata.ano>=ano && aux->ata.mes>=mes && aux->ata.dia>dia){
            printf("\nID DA ATA: %i",aux->ata.nAta);
            printf("\nData da ata %i/%i/%i",aux->ata.dia,aux->ata.mes,aux->ata.ano);
            printf("\nLOCAL DA ASSEMBLEIA %s",aux->ata.local);
            printf("\nTEXTO DA ATA:\n%s",aux->ata.texto);
            if(aux->ata.estado==1) printf("\nESTADO: EM REDAÇÃO");
            if(aux->ata.estado==2) printf("\nESTADO: PARA ASSINATURA");
            if(aux->ata.estado==3) {
                printf("\nESTADO: CONCLUÍDA");
                printf("\nEstado de aprovação: %s",aux->ata.aprovacao);
            }
            printf("\nAcionistas que faltam assinar:\n");
            imprimeStack(aux->ata.porAssinar,aux->ata.tos_porAssinar);
            printf("\nAcionistas que já assinaram:\n");
            imprimeAssinaram(aux->ata.dia_assinado,aux->ata.mes_assinado,aux->ata.ano_assinado,aux->ata.hora_assinado,
                             aux->ata.min_assinado,aux->ata.assinado,aux->ata.tos_assinado);
            printf("\nAcionistas que se recusaram a assinar:\n");
            imprimeNaoAsssinaram(aux->ata.dia_naoAssinou,aux->ata.mes_naoAssinou,aux->ata.ano_naoAssinou,
                                 aux->ata.hora_naoAssinou,aux->ata.minuto_naoAssinou,aux->ata.razao,aux->ata.naoAssinou,
                                 aux->ata.tos_naoAssinou);
        }
    }
}

void ordena_emFalta(ELEM_ATA *iniLista){
    ELEM_ATA *aux=NULL;
    int max=0;
    int i=0;
    if(iniLista==NULL){
        printf("\n\tNÃO EXISTEM ATAS");
        return;
    }

    for(aux=iniLista;aux != NULL; aux=aux->prox){
        if(max<(aux->ata.tos_porAssinar)){
            max=aux->ata.tos_porAssinar;
        }
    }

    for(i=0;i<=max;i++){
        for(aux=iniLista;aux != NULL; aux=aux->prox){
            if(aux->ata.tos_porAssinar==i){
                printf("\nID DA ATA: %i",aux->ata.nAta);
                printf("\nData da ata %i/%i/%i",aux->ata.dia,aux->ata.mes,aux->ata.ano);
                printf("\nLOCAL DA ASSEMBLEIA %s",aux->ata.local);
                printf("\nTEXTO DA ATA:\n%s",aux->ata.texto);
                if(aux->ata.estado==1) printf("\nESTADO: EM REDAÇÃO");
                if(aux->ata.estado==2) printf("\nESTADO: PARA ASSINATURA");
                if(aux->ata.estado==3) {
                    printf("\nESTADO: CONCLUÍDA");
                    printf("\nEstado de aprovação: %s",aux->ata.aprovacao);
                }
                printf("\nAcionistas que faltam assinar:\n");
                imprimeStack(aux->ata.porAssinar,aux->ata.tos_porAssinar);
                printf("\nAcionistas que já assinaram:\n");
                imprimeAssinaram(aux->ata.dia_assinado,aux->ata.mes_assinado,aux->ata.ano_assinado,aux->ata.hora_assinado,
                                 aux->ata.min_assinado,aux->ata.assinado,aux->ata.tos_assinado);
                printf("\nAcionistas que se recusaram a assinar:\n");
                imprimeNaoAsssinaram(aux->ata.dia_naoAssinou,aux->ata.mes_naoAssinou,aux->ata.ano_naoAssinou,
                                     aux->ata.hora_naoAssinou,aux->ata.minuto_naoAssinou,aux->ata.razao,aux->ata.naoAssinou,
                                     aux->ata.tos_naoAssinou);
            }
        }
    }
}
void pesquisaNaoAprovaram(ELEM_ATA *iniLista, int id_pesq){
    ELEM_ATA *aux=NULL;
    if(iniLista==NULL){
        printf("\n\tNÃO EXISTEM ATAS");
        return;
    }

    for(aux=iniLista;aux != NULL; aux=aux->prox){
        if(aux->ata.nAta==id_pesq){
            printf("\n\tAcionistas que se recusaram a assinar:\n");
            imprimeNaoAsssinaram(aux->ata.dia_naoAssinou,aux->ata.mes_naoAssinou,aux->ata.ano_naoAssinou,
                                 aux->ata.hora_naoAssinou,aux->ata.minuto_naoAssinou,aux->ata.razao,aux->ata.naoAssinou,
                                 aux->ata.tos_naoAssinou);

        }
    }
}

void acionistasOpcoes(ELEM_ATA *iniLista, char nomeAcionista[]){
    ELEM_ATA *aux=NULL;
    int opcao=0;
    char razao[MAX_RAZAO];
    if(iniLista==NULL){
        printf("\n\tNÃO EXISTEM ATAS");
        return;
    }
    for(aux=iniLista;aux != NULL; aux=aux->prox){
        if(aux->ata.estado==2){
            if(top(aux->ata.porAssinar,aux->ata.tos_porAssinar,nomeAcionista)){
                printf("\nID DA ATA: %i",aux->ata.nAta);
                printf("\nData da ata %i/%i/%i",aux->ata.dia,aux->ata.mes,aux->ata.ano);
                printf("\nLOCAL DA ASSEMBLEIA %s",aux->ata.local);
                printf("\nTEXTO DA ATA:\n%s",aux->ata.texto);
                if(aux->ata.estado==1) printf("\nESTADO: EM REDAÇÃO");
                if(aux->ata.estado==2) printf("\nESTADO: PARA ASSINATURA");
                if(aux->ata.estado==3) {
                    printf("\nESTADO: CONCLUÍDA");
                    printf("\nEstado de aprovação: %s",aux->ata.aprovacao);
                }
                while(1){
                    printf("\n\tPretende assinar esta ata? Se sim, pressione 1.Se se recursa pressione 2\n");
                    scanf("%i",&opcao);
                    if(opcao==1) break;
                    if(opcao==2) break;
                }
                if(opcao==1){
                    pop(aux->ata.porAssinar,&aux->ata.tos_porAssinar);
                    push(aux->ata.assinado,nomeAcionista,&aux->ata.tos_assinado);
                    insereDataHora(aux->ata.dia_assinado,aux->ata.mes_assinado,aux->ata.ano_assinado,aux->ata.hora_assinado
                            ,aux->ata.min_assinado,aux->ata.tos_assinado);
                    printf("\nAssinou esta ata com sucesso!");
                    verificaEstadoAta(aux->ata.tos_assinado,aux->ata.tos_naoAssinou,aux->ata.tos_porAssinar,aux->ata.aprovacao,&aux->ata.estado);
                    writeAtasBin(iniLista);
                }
                if(opcao==2){
                    printf("\n\tQual a razão de não assinar?\n");
                    fflush(stdin);
                    fgets(razao,MAX_RAZAO,stdin);
                    pop(aux->ata.porAssinar,&aux->ata.tos_porAssinar);
                    pushNaoAssinou(aux->ata.naoAssinou,aux->ata.razao,nomeAcionista,razao,&aux->ata.tos_naoAssinou);
                    insereDataHora(aux->ata.dia_naoAssinou,aux->ata.mes_naoAssinou,aux->ata.ano_naoAssinou
                            ,aux->ata.hora_naoAssinou,aux->ata.minuto_naoAssinou,aux->ata.tos_naoAssinou);
                    printf("\nRecusou a assinatura a esta ata com sucesso!\n");
                    verificaEstadoAta(aux->ata.tos_assinado,aux->ata.tos_naoAssinou,aux->ata.tos_porAssinar,aux->ata.aprovacao,&aux->ata.estado);
                    writeAtasBin(iniLista);
                }
            }
        }

    }
}

void verificaEstadoAta(int tos_assinado,int tos_naoassinou,int tos_porAssinar,char aprovacao[], int *estado){
    if(tos_porAssinar != 0) return;
    else{
        (*estado)=3;
        if(tos_naoassinou>tos_assinado){
            strcpy(aprovacao,"Reprovada");
            return;
        }
        if(tos_naoassinou<tos_assinado && tos_naoassinou != 0){
            strcpy(aprovacao,"Aprovado por maioria");
            return;
        }
        if(tos_naoassinou==0){
            strcpy(aprovacao,"Aprovado por unanimidade");
            return;
        }
    }
}

void colocaAtasparaAssinatura(ELEM_ATA *iniLista,int id_pesq){
    ELEM_ATA *aux=NULL;
    int cont=0,opcao=0;
    if(iniLista==NULL){
        printf("\n\tNÃO EXISTEM ATAS");
        return;
    }
    for(aux=iniLista;aux != NULL; aux=aux->prox){
        if(id_pesq==aux->ata.nAta){
            cont ++;
            if(aux->ata.estado==2){
                printf("\n\tA ata já se encontra para assinatura");
            }
            if(aux->ata.estado==1){
                printf("\nID DA ATA: %i",aux->ata.nAta);
                printf("\nData da ata %i/%i/%i",aux->ata.dia,aux->ata.mes,aux->ata.ano);
                printf("\nLOCAL DA ASSEMBLEIA %s",aux->ata.local);
                printf("\nTEXTO DA ATA:\n%s",aux->ata.texto);
                if(aux->ata.estado==1) printf("\nESTADO: EM REDAÇÃO");
                if(aux->ata.estado==2) printf("\nESTADO: PARA ASSINATURA");
                if(aux->ata.estado==3) {
                    printf("\nESTADO: CONCLUÍDA");
                    printf("\nEstado de aprovação: %s",aux->ata.aprovacao);
                }
                printf("\nAcionistas que faltam assinar:\n");
                imprimeStack(aux->ata.porAssinar,aux->ata.tos_porAssinar);
                printf("\nAcionistas que já assinaram:\n");
                imprimeAssinaram(aux->ata.dia_assinado,aux->ata.mes_assinado,aux->ata.ano_assinado,aux->ata.hora_assinado,
                                 aux->ata.min_assinado,aux->ata.assinado,aux->ata.tos_assinado);
                printf("\nAcionistas que se recusaram a assinar:\n");
                imprimeNaoAsssinaram(aux->ata.dia_naoAssinou,aux->ata.mes_naoAssinou,aux->ata.ano_naoAssinou,
                                     aux->ata.hora_naoAssinou,aux->ata.minuto_naoAssinou,aux->ata.razao,aux->ata.naoAssinou,
                                     aux->ata.tos_naoAssinou);
                writeAtasBin(iniLista);
                cont++;

                printf("\n\n\tPRETENDE COLOCAR ESTA ATA PARA ASSINATURA?Digite 1 para sim, ou qualquer outra tecla para não\n");
                fflush(stdin);
                scanf("%i",&opcao);
                if(opcao==1){
                    aux->ata.estado=2;
                    printf("\nCOLOCOU A ATA PARA ASSINATURA COM COM SUCESSO!!!");
                    writeAtasBin(iniLista);
                }
            }
        }
    }
    if(cont==0){
        printf("\nAta não existe");
    }
}

void removeAta(ELEM_ATA **iniLista, int idRemover){
    ELEM_ATA *aux=*iniLista, *ant=NULL;

    if (*iniLista==NULL){
        printf("\n\tLista não existe\n");
        return;
    }
    while(aux!=NULL && aux->ata.nAta != idRemover) {
        ant=aux;
        aux=aux->prox;
    }
    if(aux==NULL){
        printf("\n\tAta não encontrada!!!\n");
        return;
    }
    if(ant==NULL){
        printf("\n\tA remover ata...");
        *iniLista= aux->prox;
        printf("\n\tAta remvida com sucesso!!\n");
    }
    else{
        printf("\n\tA remover ata...");
        ant->prox=aux->prox;
        printf("\n\tAta remvido com sucesso!!\n");
    }
    free(aux);
}

/*void colocarAtaAssinatura(ELEM_ATA *iniLista, int id){
    ELEM_ATA *aux=NULL;
    int cont=0;
    for(aux=iniLista;aux != NULL; aux=aux->prox){
        if(id==aux->ata.nAta){
            if(aux->ata.estado==2){
                printf("\nA ata já se encontra para assinatura!!");
                return;
            }
            if(aux->ata.estado==1){
                aux->ata.estado=2;
                printf("\nAta colocada com sucesso no estado: PARA ASSINATURA!!");
                return;
            }
            cont ++;
        }
    }
    if(cont==0){
        printf("\n\tNão existem atas com esse id\n");
    }
}*/

void indicaAtasPorAssinar(ELEM_ATA *iniLista,char acionistaProcura[]){
    ELEM_ATA *aux=NULL;
    int cont=0;
    printf("\n\tAtas que tem por assinar:\n");
    for(aux=iniLista;aux != NULL; aux=aux->prox){
        if(aux->ata.estado==2){
            if(verificaSeExiste(aux->ata.porAssinar,aux->ata.tos_porAssinar,acionistaProcura)){
                printf("\nID: %i",aux->ata.nAta);
                cont ++;
            }
        }
    }
    if(cont==0){
        printf("\nO acionista que está a procura não tem nenhuma ata por assinar");
    }
}

void passaAtaFicheiroTxt(ELEM_ATA *iniLista, char nomeFicheiro[],int id_pesq){
    ELEM_ATA *aux=NULL;
    FILE *fp=NULL;
    int i=0,cont=0;
    if(iniLista==NULL){
        printf("\n\tNÃO EXISTEM ATAS");
        return;
    }
    fp=fopen(nomeFicheiro,"w");
    if(fp==NULL){
        printf("\nHOUVE UM ERRO NA GERAÇÃO Do FICHEIRO");
        return;
    }
    for(aux=iniLista;aux != NULL; aux=aux->prox){
        if(aux->ata.nAta==id_pesq){
            cont ++;
            fprintf(fp,"\nID DA ATA: %i",aux->ata.nAta);
            fprintf(fp,"\nDATA DA ATA: %i/%i/%i",aux->ata.dia,aux->ata.mes,aux->ata.ano);
            fprintf(fp,"\nLOCAL DA ASSEMBLEIA: %s",aux->ata.local);
            fprintf(fp,"\nTexto da ata: %s",aux->ata.texto);
            if(aux->ata.estado==1) fprintf(fp,"\nESTADO: EM REDAÇÃO");
            if(aux->ata.estado==2) fprintf(fp,"\nESTADO: PARA ASSINATURA");
            if(aux->ata.estado==3) {
                fprintf(fp,"\nESTADO: CONCLUÍDA");
                fprintf(fp,"\nEstado de aprovação: %s",aux->ata.aprovacao);
            }
            fprintf(fp,"\n\nASSINATURAS:\n");
            fprintf(fp,"\nACIONISTAS QUE FALTAM ASSINAR:");
            for(i=0;i<aux->ata.tos_porAssinar;i++){
                fprintf(fp,"\n\t%s",aux->ata.porAssinar[i]);
            }
            fprintf(fp,"\n\nACIONISTAS QUE JA ASSINARAM:");
            for(i=0;i<aux->ata.tos_assinado;i++){
                fprintf(fp,"\n\tNOME:%s",aux->ata.assinado[i]);
                fprintf(fp,"\tHORA: %i:%i",aux->ata.hora_assinado[i],aux->ata.min_assinado[i]);
                fprintf(fp,"\n\tDATA DA ASSINATURA: %i/%i/%i",aux->ata.dia_assinado[i],aux->ata.mes_assinado[i]
                ,aux->ata.ano_assinado[i]);
            }
            fprintf(fp,"\n\nACIONISTAS QUE SE RECUSARAM A ASSINAR");
            for(i=0;i<aux->ata.tos_naoAssinou;i++){
                fprintf(fp,"\n\tNOME: %s",aux->ata.naoAssinou[i]);
                fprintf(fp,"\tRAZÃO: %s",aux->ata.razao[i]);
                fprintf(fp,"\n\tHORA: %i:%i",aux->ata.hora_naoAssinou[i],aux->ata.minuto_naoAssinou[i]);
                fprintf(fp,"\n\tDATA DA ASSINATURA %i/%i/%i",aux->ata.dia_naoAssinou[i]
                        ,aux->ata.mes_naoAssinou[i],aux->ata.ano_naoAssinou[i]);
            }
        }
    }
    if(cont==0){
        printf("\nNÃO EXISTEM ATAS COM O ID INTRODUZIDO");
    }
    fclose(fp);
}

void passaCsv(int nAta, ELEM_USER *iniLista, ELEM_ATA **iniAta){
    char nomeFicheiro[100], nomeAcionista[20];
    int nAcionistas = 0, opcao = 0, i = 0, res = 0;
    FILE *fp = NULL;
    ATA new_ata;

    new_ata.nAta = nAta + 1;
    new_ata.tos_porAssinar = 0;
    new_ata.tos_assinado = 0;
    new_ata.tos_naoAssinou = 0;
    do{
        printf("\nIntroduza o nome do ficheiro que pretende importar\n");
        fflush(stdin);
        gets(nomeFicheiro);
    } while ((fp = fopen(nomeFicheiro, "r")) == NULL);
    if ((fp = fopen(nomeFicheiro, "r")) != NULL){
        while ((res = fscanf(fp, "%i/%i/%i;%[^\n]\n", &new_ata.ano, &new_ata.mes, &new_ata.dia, new_ata.local)) != EOF){
            new_ata.nAta=nAta+1;
            printf("\nID DA ATA: %i\n",new_ata.nAta);
            new_ata.estado = 1;
            insereIniLL(iniAta, new_ata);
        }
    }
    fclose(fp);
}
