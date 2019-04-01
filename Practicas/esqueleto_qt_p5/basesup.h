#ifndef BASESUP_H
#define BASESUP_H

#include "brazo.h"

class baseSup
{

    brazo brz;
    cilindro basesup;
    GLfloat alfa1 = 0;

public:
    baseSup(int, int);
    void dibujar (int, char);
};

#endif // BASESUP_H
