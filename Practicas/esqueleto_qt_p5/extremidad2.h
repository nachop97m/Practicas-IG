#ifndef EXTREMIDAD2_H
#define EXTREMIDAD2_H

#include "cilindro.h"
#include "esfera.h"
#include "cubo.h"

class extremidad2
{
    cilindro cl;
    GLfloat alfa2 = 0;
public:
    extremidad2(int, int);
    void dibujar (int, char);
};

#endif // EXTREMIDAD2_H
