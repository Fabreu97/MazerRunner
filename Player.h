#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Position.h"

typedef struct
{
    char simbolo;
    int status; // 1 pra vivo e 0 pra morto
    Position inicial;
    Position atual;

}Player;

Player* criaPlayer();
void destroiPlayer(Player* jogador);
void mostraStatus(Player* jogador);

#endif

