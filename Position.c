#include "Position.h"
#include <stdlib.h>

Position * criarPosition()
{
    Position *p = (Position *) malloc(sizeof(Position));

    if(p != NULL)
    {
        p->dado = '#';
        p->x = 0;
        p->y = 0;
        p->rastro = -1;
    }

    return p;
}

void destroiPosition(Position *p)
{
    free(p);
    p = NULL;
}

