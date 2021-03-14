#include "Maze.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

Maze* criarMaze(int linhas, int colunas)
{
    //aloca um TAD do tipo MAZE
    Maze *m = (Maze *) malloc(sizeof(Maze));

    if(m != NULL)
    {
        int i;

        m->linhas = linhas;
        m->colunas = colunas;

        //aloca o vetor de vetores para armazenar as linhas da matriz
        m->matriz = (Position **) malloc(sizeof(Position *) * linhas);

        for(i = 0; i < linhas; i++)
        {
            //aloca cada linha da matriz
            m->matriz[i] = (Position *) malloc(sizeof(Position) * colunas);
        }
    }
    return m;
}

void carregarDadosDoArquivo(Maze *maze, Player* jogador, Inimigo* monstros,Saida* s, char * nomeArquivo)
{
    int i;
    int teste;

    FILE *file = fopen(nomeArquivo, "r");

    if(file == NULL)
    {
        printf("erro ao abrir o arquivo - confira o nome ou o local onde o arquivo maze.txt foi salvo\n");
    }
    else
    {
        ///carregando elementos----------------------------
        fscanf(file, "%d %d\n", &jogador->atual.y,&jogador->atual.x);
        fscanf(file, "%d %d\n", &monstros[0].inicial.y,&monstros[0].inicial.x);
        fscanf(file, "%d %d\n", &monstros[1].inicial.y,&monstros[1].inicial.x);
        fscanf(file, "%d %d\n", &monstros[2].inicial.y,&monstros[2].inicial.x);
        fscanf(file, "%d %d\n", &monstros[3].inicial.y,&monstros[3].inicial.x);
        fscanf(file, "%d %d\n", &s->saida.y, &s->saida.x);

        //Player
        jogador->inicial.x = jogador->atual.x;
        jogador->inicial.y = jogador->atual.y;
        jogador->simbolo = 'X';
        jogador->status = 1;
        jogador->inicial.rastro = -1;

        //Monstros
        for(i = 0;i < 4;i++)
        {
            if(monstros[i].inicial.y > 0)
            {
                monstros[i].atual.y = monstros[i].inicial.y;
                monstros[i].atual.x = monstros[i].inicial.x;
                monstros[i].simbolo = 49;
                monstros[i].salto = 1;
            }
            else
            {
                monstros[i].status = 0;
                teste = monstros[i].inicial.y * (-1) -1;
                monstros[teste].simbolo += 1;
                monstros[teste].salto += 1;
            }
        }


        //Saida
        s->saida.dado = 'S';
        s->simbolo = 'S';

        ///carregando labirinto-------------------------
        char buffer[200];
        int i = 0, j, z;

        while(fscanf(file, "%[^\n]\n", buffer) != EOF)
        {
            j = 0;
            z = 0;

            while(buffer[z] != '\0')
            {
                if(buffer[z] != ';')
                {
                    maze->matriz[i][j].dado = buffer[z];
                    maze->matriz[i][j].x = 0;
                    maze->matriz[i][j].y = 0;
                    maze->matriz[i][j].rastro = -1;
                    j++;
                }
                z++;
            }
            i++;
        }

        ///escrevendo elementos do jogo no labirinto

        fclose(file);
    }
}

void destroiMaze(Maze *maze)
{
    int i;

    //desaloca todos as linhas
    for(i = 0; i < maze->linhas; i++)
    {
        free(maze->matriz[i]);
        maze->matriz[i] = NULL;
    }

    //desaloca o vetor de vetores
    free(maze->matriz);
    maze->matriz = NULL;

    //desaloca o TAD do tipo Maze
    free(maze);
    maze = NULL;
}

void exibirLabirinto(Maze* maze, Inimigo* inimigos, Player* jogador, int quant,Saida* s)
{
    int i, j;
    printf("\n");
    mostraStatus(jogador);

    //inimigo morto
    for(i = 0; i < quant; i++)
    {
        if(inimigos[i].status == 0)
        {
            maze->matriz[inimigos[i].atual.y][inimigos[i].atual.x].dado = '.';
        }
    }

    //mudar jogador
    maze->matriz[jogador->inicial.y][jogador->inicial.x].dado = '.';
    maze->matriz[jogador->atual.y][jogador->atual.x].dado = jogador->simbolo;

    //mudar inimigos
    for(i = 0; i < quant; i++)
    {
        if(inimigos[i].status)
        {
            maze->matriz[inimigos[i].inicial.y][inimigos[i].inicial.x].dado = '.';
            maze->matriz[inimigos[i].atual.y][inimigos[i].atual.x].dado = inimigos[i].simbolo;
        }
    }

    //saida
    maze->matriz[s->saida.y][s->saida.x].dado = s->simbolo;

    for(i = 0; i < maze->linhas; i++)
    {
        for(j = 0; j < maze->colunas; j++)
        {
            printf("%2c ",maze->matriz[i][j].dado);
        }
        printf("\n");
    }
}

void moverPlayer(Player* jogador, Maze* labirinto)
{
    char locomover;
    int invalido = 1;
    int vitoria = 0;

    while(invalido)
    {
        printf("Mova: ");
        scanf("%c",&locomover);
        fflush(stdin);
        jogador->inicial.y = jogador->atual.y;
        jogador->inicial.x = jogador->atual.x;
        if(locomover == 'w')
        {
            if(labirinto->matriz[jogador->atual.y - 1][jogador->atual.x].dado == 'S')
            {
                vitoria = 1;
            }
            if(labirinto->matriz[jogador->atual.y - 1][jogador->atual.x].dado == '.' || vitoria)
            {
                jogador->atual.y -= 1;
                invalido = 0;
                vitoria = 0;
            }
        }
        else if(locomover == 'a')
        {
            if(labirinto->matriz[jogador->atual.y][jogador->atual.x - 1].dado == 'S')
            {
                vitoria = 1;
            }
            if(labirinto->matriz[jogador->atual.y][jogador->atual.x - 1].dado == '.' || vitoria)
            {
                jogador->atual.x -= 1;
                invalido = 0;
                vitoria = 0;
            }
        }
        else if(locomover == 'd')
        {
            if(labirinto->matriz[jogador->atual.y][jogador->atual.x + 1].dado == 83)
            {
                vitoria = 1;
            }
            if((labirinto->matriz[jogador->atual.y][jogador->atual.x + 1].dado == '.') || vitoria)
            {
                jogador->atual.x += 1;
                invalido = 0;
                vitoria = 0;
            }
        }
        else if(locomover == 's')
        {
            if(labirinto->matriz[jogador->atual.y + 1][jogador->atual.x].dado == 'S')
            {
                vitoria = 1;
            }
            if((labirinto->matriz[jogador->atual.y + 1][jogador->atual.x].dado == '.') || vitoria)
            {
                jogador->atual.y += 1;
                invalido = 0;
                vitoria = 0;
            }
        }
        invalido = 0;
    }
}

int* criaVetorSondagem(int quant_monstros)
{
    int* sondagem = (int*)calloc(quant_monstros,sizeof(int));
    return(sondagem);
}

void destroiSondagem(int* son)
{
    free(son);
    son = NULL;
}

void sondagemMonstros(Inimigo* inimigos, Maze* m,Player* p, int quant, int* sondagem)
{
    //1 = é para esquerda
    //2 = é para a direita
    //3 = é para cima
    //4 = é para baixo
    int i,j;
    int saida1,saida2,saida3,saida4;
    int cx,cy;

    for(i = 0;i < quant; i++)
    {
        saida1 = 0;
        saida2 = 0;
        saida3 = 0;
        saida4 = 0;

        for(j = 1; j < 8; j++)
        {
            //1
            cy = inimigos[i].atual.y;
            cx = inimigos[i].atual.x - j;
            if(cx <= 0)
            {
                saida1 = 1;
            }
            if(!saida1 && m->matriz[cy][cx].dado != '#')
            {
                if(m->matriz[cy][cx].dado == 'X')
                {
                    inimigos[i].alvo.y = cy;
                    inimigos[i].alvo.x = cx;
                    sondagem[i] = 1; // monstro i tem uma posição alvo
                    saida1 = 1;
                }
            }
            else
            {
                saida1 = 1;
            }
            //2
            cy = inimigos[i].atual.y;
            cx = inimigos[i].atual.x + j;
            if(cx >= 21)
            {
                saida2 = 1;
            }
            if(!saida2 && m->matriz[cy][cx].dado != '#')
            {
                if(m->matriz[cy][cx].dado == 'X')
                {
                    inimigos[i].alvo.y = cy;
                    inimigos[i].alvo.x = cx;
                    sondagem[i] = 2; // monstro i tem uma posição alvo
                    saida2 = 1;
                }
            }
            else
            {
                saida2 = 1;
            }
            //3
            cy = inimigos[i].atual.y - j;
            cx = inimigos[i].atual.x;
            if(cy <= 0)
            {
                saida3 = 1;
            }
            if(!saida3 && m->matriz[cy][cx].dado != '#')
            {
                if(m->matriz[cy][cx].dado == 'X')
                {
                    inimigos[i].alvo.y = cy;
                    inimigos[i].alvo.x = cx;
                    sondagem[i] = 3; // monstro i tem uma posição alvo
                    saida3 = 1;
                }
            }
            else
            {
                saida3 = 1;
            }
            //4
            cy = inimigos[i].atual.y + j;
            cx = inimigos[i].atual.x;
            if(cy >= 21)
            {
                saida4 = 1;
            }
            if(!saida4 && m->matriz[cy][cx].dado != '#')
            {
                if(m->matriz[cy][cx].dado == 'X')
                {
                    inimigos[i].alvo.y = cy;
                    inimigos[i].alvo.x = cx;
                    sondagem[i] = 4; // monstro i tem uma posição alvo
                    saida4 = 1;
                }
            }
            else
            {
                saida4 = 1;
            }
        }
    }
}

void moverInimigos(Inimigo* inimigos, Maze* m, Player* p, int quant, int* sondagem)
{
    int i;
    int andar;
    int sorteio;
    int flag;

    //1 = é para esquerda que devo ir
    //2 = é para a direita que devo ir
    //3 = é para cima que devo ir
    //4 = é para baixo que devo ir

    srand(time(NULL));
    for(i = 0; i < quant; i++)
    {
        flag = 0;
        if(inimigos[i].status)
        {
            inimigos[i].inicial.x = inimigos[i].atual.x;
            inimigos[i].inicial.y = inimigos[i].atual.y;
            andar = inimigos[i].salto;
            sorteio = rand()%4 + 1;
            while(andar)
            {
                if(sondagem[i] == 1)
                {
                    inimigos[i].atual.x -= 1;
                    andar--;
                    if(inimigos[i].atual.x == inimigos[i].alvo.x)
                    {
                        sondagem[i] = 0;
                        andar = 0;
                    }
                }
                else if(sondagem[i] == 2)
                {
                    inimigos[i].atual.x += 1;
                    andar--;
                    if(inimigos[i].atual.x == inimigos[i].alvo.x)
                    {
                        sondagem[i] = 0;
                        andar = 0;
                    }
                }
                else if(sondagem[i] == 3)
                {
                    inimigos[i].atual.y -= 1;
                    andar--;
                    if(inimigos[i].atual.y == inimigos[i].alvo.y)
                    {
                        sondagem[i] = 0;
                        andar = 0;
                    }
                }
                else if(sondagem[i] == 4)
                {
                    inimigos[i].atual.y += 1;
                    andar--;
                    if(inimigos[i].atual.y == inimigos[i].alvo.y)
                    {
                        sondagem[i] = 0;
                        andar = 0;
                    }
                }
                else
                {
                    if(sorteio == 1)
                    {
                        if(m->matriz[inimigos[i].atual.y][inimigos[i].atual.x - 1].dado != '#')
                        {
                            inimigos[i].atual.x -= 1;
                            andar--;
                            flag = 1;
                        }
                        else if(flag)
                        {
                            andar = 0;
                        }
                        else
                        {
                            sorteio = rand()%4 + 1;
                        }
                    }
                    else if(sorteio == 2)
                    {
                        if(m->matriz[inimigos[i].atual.y][inimigos[i].atual.x + 1].dado != '#')
                        {
                            inimigos[i].atual.x += 1;
                            andar--;
                        }
                        else if(flag)
                        {
                            andar = 0;
                        }
                        else
                        {
                            sorteio = rand()%4 + 1;
                        }

                    }
                    else if(sorteio == 3)
                    {
                        if(m->matriz[inimigos[i].atual.y - 1][inimigos[i].atual.x].dado != '#')
                        {
                            inimigos[i].atual.y -= 1;
                            andar--;
                        }
                        else if(flag)
                        {
                            andar = 0;
                        }
                        else
                        {
                            sorteio = rand()%4 + 1;
                        }
                    }
                    else if(sorteio == 4)
                    {
                        if(m->matriz[inimigos[i].atual.y + 1][inimigos[i].atual.x].dado != '#')
                        {
                            inimigos[i].atual.y += 1;
                            andar--;
                        }
                        else if(flag)
                        {
                            andar = 0;
                        }
                        else
                        {
                            sorteio = rand()%4 + 1;
                        }

                    }

                }
                teste_de_derrota(p,inimigos,quant);
            }
        }
    }

}

void teste_de_derrota(Player* j, Inimigo* inimigos, int quant)
{
    int i;
    for(i = 0; i < quant;i++)
    {
        if(inimigos[i].status)
        {
            if((inimigos[i].atual.y == j->atual.y) && (inimigos[i].atual.x == j->atual.x))
            {
                j->status = 0;
                i = quant;
            }
        }
    }
}

void fusao_monstros(Maze* m, Inimigo* inimigos,int quant)
{
    int i,j;
    int flag = 0;

    for(i = 0; i < (quant - 1); i++)
    {
        for(j = i + 1; j < quant; j++)
        {
            if(inimigos[i].status && inimigos[j].status)
            {
                if(inimigos[i].atual.y == inimigos[j].atual.y)
                {
                    flag = 1;
                }
                if(flag && (inimigos[i].atual.x == inimigos[j].atual.x))
                {
                    inimigos[i].status += 1;
                    inimigos[i].salto = inimigos[i].salto + inimigos[j].salto;
                    inimigos[i].simbolo += inimigos[j].simbolo - 48;

                    //inimigos[j].atual.y = -i -1;
                    //inimigos[j].atual.x = -i -1;
                    inimigos[j].status = 0;
                    inimigos[j].salto = 0;
                }
            }
        }
    }
}

void salvarJogo(Player* jogador, Inimigo* monstros, Maze* labirinto, Saida* s, int quant) // save game
{
	FILE* arquivo = fopen("mazeS.txt", "w");
	int i, j, k;

	fprintf(arquivo, "%d %d\n",jogador->atual.y, jogador->atual.x);

	for(i = 0; i < quant;i++)
    {
        fprintf(arquivo, "%d %d\n", monstros[i].atual.y, monstros[i].atual.x);
    }
    fprintf(arquivo, "%d %d\n",s->saida.y, s->saida.x);
    for(i = 0; i < LIN; i++)
    {
        for(j = 0; j < COL; j++)
        {
            for(k = 0; k < 10; k++)
            {

                if((labirinto->matriz[i][j].dado == 48 + k) || (labirinto->matriz[i][j].dado == 'X') || (labirinto->matriz[i][j].dado == 'S'))
                {
                    labirinto->matriz[i][j].dado = '.';
                }
            }
            fprintf(arquivo,"%c",labirinto->matriz[i][j].dado);

            if(j < COL - 1)
			{
				fprintf(arquivo, ";");
			}
        }
        fprintf(arquivo, "\n");
    }
	fclose(arquivo);
}

void menuJogo(Maze* m, char** nome)
{
    int menu = 1;

    char selecao1 = 'X',selecao2 = ' ',selecao3;

    while(menu)
    {
        printf("(%c) New Game\n",selecao1);
        printf("(%c) Load Game\n",selecao2);
        scanf("%c",&selecao3);
        fflush(stdin);

        switch(selecao3)
        {
        case 'w':
            selecao1 = 'X';
            selecao2 = ' ';
            break;
        case 's':
            selecao1 = ' ';
            selecao2 = 'X';
            break;
        case 'x':
            menu = 0;
            break;
        default:
            menu = 1;
        }
        system("cls");
    }

    if(selecao1 == 'X')
    {
        menu = rand()%4 + 1;
        *nome = "maze4.txt";
    }
    else
    {
        *nome = "mazeS.txt";
        *nome[9] = '\0';
    }
}

void rastroPlayer(Player* jogador,Maze* labirinto)
{
    jogador->inicial.rastro += 1;
    labirinto->matriz[jogador->inicial.y][jogador->inicial.x].rastro = jogador->inicial.rastro;
}
