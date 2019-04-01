#ifndef BRAZO_H
#define BRAZO_H

#include "cilindro.h"
#include "esfera.h"
#include "cubo.h"
#include "extremidad.h"
#include "extremidad2.h"

class brazo
{
    extremidad ext;
    extremidad2 ext2;
    cilindro cl;
    GLfloat alfa1 = 0;
public:
    brazo(int, int);
    void dibujar (int, char);
};

#endif // BRAZO_H
