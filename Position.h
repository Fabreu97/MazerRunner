#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED

typedef struct
{
    char dado;
    int x;
    int y;
    int rastro;
}Position;

Position * criarPosition();
void destroiPosition(Position *p);

#endif // POSITION_H_INCLUDED

