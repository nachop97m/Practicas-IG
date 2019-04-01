#ifndef BASEMED_H
#define BASEMED_H

#include "basesup.h"

class baseMed
{
    cilindro basemed;
    cubo basemed2;
    baseSup bsp;
    double pos1 = 11.3;
    double pos2 = 7;

public:
    baseMed(int, int);
    void dibujar(int, char);
};

#endif // BASEMED_H
