#ifndef TABLERO_H
#define TABLERO_H

#include "o3d.h"
#include <QImage>


class tablero : public O3D
{

public:
    tablero(int x, int y);
    void imagen(int a, int b, int c, int d, bool t);
private:
    QImage Imagen;

};

#endif // TABLERO_H
