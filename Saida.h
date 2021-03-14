#ifndef SAIDA_H_INCLUDED
#define SAIDA_H_INCLUDED

#include "Position.h"

typedef struct
{
    char simbolo;
    Position saida;

}Saida;

Saida* criaSaida();
void destroiSaida(Saida* s);

#endif
