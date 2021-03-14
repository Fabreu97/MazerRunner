#include "Player.h"
#include <stdio.h>
#include <stdlib.h>

Player * criaPlayer()
{
    Player* jogador;
    jogador = (Player*)malloc(sizeof(Player));
    if(jogador != NULL)
    {
        jogador->status = 1;
    }
    return(jogador);
}
void destroiPlayer(Player* jogador)
{
    free(jogador);
    jogador = NULL;
}
void mostraStatus(Player* jogador)
{

        printf("Status: %d\n\n",jogador->status);
        printf("\n\nCoordenadas do Player:");
        printf("\nx = %d",jogador->atual.x);
        printf("\ny = %d \n\n",jogador->atual.y);
}
