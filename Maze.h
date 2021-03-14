#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include "Position.h"
#include "Player.h"
#include "Inimigo.h"
#include "Saida.h"

#define LIN 21
#define COL 21


typedef struct
{
    int linhas;
    int colunas;
    Position **matriz;

}Maze;

/*
 * Cria o labirinto e a matriz de jogo em memória
 * Importante: os campos da matriz não são inicializados
 */
Maze * criarMaze(int linhas, int colunas);

/*
 * Inicializa o labirinto a partir de um arquivo de texto (carrega as informações para o campo dado)
 * O nome do arquivo deve ser passado como argumento para a função
 * Os demais campos de cada célula da matriz são inicializados da seguinte forma:
 * x = 0, y = 0 e rastro = -1
 */
void carregarDadosDoArquivo(Maze *maze, Player* jogador, Inimigo* monstros,Saida* s, char * nomeArquivo);

/*
 * Libera a memória alocada para qualquer TAD do tipo Maze
 */
void destroiMaze(Maze *maze);

/*
 * Exibe o conteúdo do labirinto, somente o campo dado
 */
void exibirLabirinto(Maze* maze, Inimigo* inimigos, Player* jogador, int quant,Saida* s);

/*
 * Move o player no Maze
 */
void moverPlayer(Player* jogador, Maze* labirinto);

/*
 * Cria o vetor flag sondagem
 */
int* criaVetorSondagem(int quant_monstros);

 /*
  * Destroi Vetor de flag Sondagem
  */
void destroiSondagem(int* son);

/*
 * Faz a sondagem e passa a coordenadas do alvo por referencia e preenche a flag sondagem
 */
void sondagemMonstros(Inimigo* inimigos, Maze* m,Player* p, int quant, int* sondagem);

/*
 * Mover os inimigos na TADS deles
 */
void moverInimigos(Inimigo* inimigos, Maze* m, Player* p, int quant, int* sondagem);

/*
 *
 */
void teste_de_derrota(Player* j, Inimigo* inimigos, int quant);

/*
 * Fusão de Monstros
 */
void fusao_monstros(Maze* m, Inimigo* inimigos,int quant);

/*
 * Salvar jogo
 */
void salvarJogo(Player* jogador, Inimigo* monstros, Maze* labirinto, Saida* s, int quant);

/*
 * Menu do jogo
 */
void menuJogo(Maze* m, char** nome);

/*
 * Deixa o rastro do Player no Labirinto
 */
void rastroPlayer(Player* jogador,Maze* labirinto);

#endif // MAZE_H_INCLUDED

