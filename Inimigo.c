#include "Inimigo.h"
#include <stdio.h>
#include <stdlib.h>

Inimigo* criaInimigos()
{
    Inimigo* monsters;

    monsters = (Inimigo*)malloc(sizeof(Inimigo));

    monsters->simbolo = '1'; //49 é o caracter '1' na tabela asc
    monsters->salto = 1;
    monsters->status = 1;

    return(monsters);
}
Inimigo* criaVInimigos(int quant)
{
    int i;
    Inimigo* monstros;

    if(quant > 9)
    {
        quant = 9;
    }
    monstros = (Inimigo*)malloc(sizeof(Inimigo)*quant);

    if(monstros != NULL)
    {
        for(i = 0; i < quant; i++)
        {
            monstros[i].simbolo = '1'; //49 é o caracter '1' na tabela asc
            monstros[i].salto = 1;
            monstros[i].status = 1;
        }
    }
    return(monstros);
}
void destroiInimigo(Inimigo* monster)
{
    free(monster);
    monster = NULL;
}
