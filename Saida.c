#include "Saida.h"
#include <stdio.h>
#include <stdlib.h>

Saida* criaSaida()
{
    Saida* s;
    s = (Saida*)malloc(sizeof(Saida));
    return(s);
}
void destroiSaida(Saida* s)
{
    free(s);
    s = NULL;
}


