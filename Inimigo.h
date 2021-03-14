#ifndef INIMIGO_H_INCLUDED
#define INIMIGO_H_INCLUDED

#include "Position.h"

typedef struct
{
    char simbolo;
    int status;
    int salto;
    Position alvo;
    Position inicial;
    Position atual;

}Inimigo;

Inimigo* criaInimigos();
Inimigo* criaVInimigos(int quant);
void destroiInimigo(Inimigo* monster);


#endif
