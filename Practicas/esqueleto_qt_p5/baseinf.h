#ifndef BASEINF_H
#define BASEINF_H

#include "ejerotacion.h"

class baseInf
{
    cubo basei;
    ejeRotacion eje;
    GLfloat desp;

public:
    baseInf(int, int);
    void dibujar (int, char);
    GLfloat getDesp();
    void setDesp(GLfloat);
};

#endif // BASEINF_H
