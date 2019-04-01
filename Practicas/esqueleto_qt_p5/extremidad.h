#ifndef EXTREMIDAD_H
#define EXTREMIDAD_H

#include "cilindro.h"
#include "esfera.h"
#include "cubo.h"
#include "o3dply.h"

class extremidad
{
    cilindro ext;
    esfera es;
   // O3DPLY bet;
public:
    extremidad(int, int);
    void dibujar (int);
};

#endif // EXTREMIDAD_H
