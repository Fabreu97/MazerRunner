#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Maze.h"

#define LINHAS 21
#define COLUNAS 21
#define QTDMONSTROS 4
#define NOME_ARQUIVO "savegame.txt" //arquivo de texto localizado na raiz do projeto

int main()
{
    //construtor
    setlocale(LC_ALL, "portuguese");
    int qtdmonstros = QTDMONSTROS;
    int* sondagem = criaVetorSondagem(qtdmonstros);
    char* nome = (char*)malloc(sizeof(char)*10);
    Maze* m = criarMaze(LINHAS, COLUNAS);
    Player* j = criaPlayer();
    Inimigo* monstros = criaVInimigos(qtdmonstros);
    Saida* s = criaSaida();

    //Carrega configurações iniciais do jogo carregado
    //system("MODE con cols=150 lines=60");
    //system("title Tela Full Screen");
    menuJogo(m,&nome);
    printf("A");
    carregarDadosDoArquivo(m,j,monstros,s,nome);
    printf("B");
    printf("\n\n Saida: %d %d\n\n",s->saida.x,s->saida.y);
    //carregarDadosDoArquivoDiferente(m,nome);
    //acharPlayer(j,m);
    //acharSaida(s,m);
    //acharInimigosS(monstros,m,qtdmonstros);

    /*printf("%d Coordenadas monstro 01: \nx = %d \ny = %d\n\n",monstros[0].salto,monstros[0].atual.x,monstros[0].atual.y);
    printf("%d Coordenadas monstro 02: \nx = %d \ny = %d\n\n",monstros[1].salto,monstros[1].atual.x,monstros[1].atual.y);
    printf("%d Coordenadas monstro 03: \nx = %d \ny = %d\n\n",monstros[2].salto,monstros[2].atual.x,monstros[2].atual.y);
    printf("%d Coordenadas monstro 04: \nx = %d \ny = %d\n\n",monstros[3].salto,monstros[3].atual.x,monstros[3].atual.y);*/


    //Processos do jogo em andamento
    while(j->status && !((j->atual.y == s->saida.y) && (j->atual.x == s->saida.x)))
    {
        exibirLabirinto(m,monstros,j,qtdmonstros,s);
        sondagemMonstros(monstros,m,j,qtdmonstros,sondagem);
        printf("\n%d %d %d %d\n\n",sondagem[0],sondagem[1],sondagem[2],sondagem[3]);
        printf("\n\n%d\n\n",m->matriz[j->inicial.y][j->inicial.x].rastro);
        moverPlayer(j,m);
        rastroPlayer(j,m);
        printf("\n\n%d\n\n",m->matriz[j->inicial.y][j->inicial.x].rastro);
        fflush(stdin);
        moverInimigos(monstros,m,j,qtdmonstros,sondagem);
        fusao_monstros(m,monstros,qtdmonstros);
        system("cls");
        salvarJogo(j,monstros,m,s,qtdmonstros);
        //salvarJogoDiferente(j,monstros,m,s,qtdmonstros);
    }
    if(j->status)
    {

        printf("\t\tCONGRATULATIONS\n\n\n\t\t\t\t\t\tVocê Venceu !!\n");
    }
    else
    {
        printf("\n\n\t\tYOU LOSE!!!\n\n");
    }
    //destruidor
    destroiSondagem(sondagem);
    destroiSaida(s);
    destroiInimigo(monstros);
    destroiPlayer(j);
    destroiMaze(m);

    return 0;
}
