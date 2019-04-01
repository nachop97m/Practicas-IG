#ifndef O3D_H
#define O3D_H

#include <o3ds.h>
#include <QImage>

class O3D : public O3DS
{

public:
    O3D();
    O3D( vector <_vertex3i> &, vector <_vertex3f> );
    void aniadirVertice(int, int, int, float, float, float);
    void pintarLineas();
    void pintarCarass();
    void pintarAjedrez();
    void dibujar (int);
    void normalesTriangulos();
    void normalesVertices();
    void suavizado_plano(bool l, bool l1, bool l2, float a, float b, float c, float d, GLfloat alfa, GLfloat beta, int cont);
    void suavizado_gouraud(bool l, bool l1, bool l2, float a, float b, float c, float d, GLfloat alfa, GLfloat beta, int cont);
    void textura(double a, double b, int modo);



protected:
   vector <_vertex3i> triangulos;
   vector <_vertex3f> normalesT;
   vector <_vertex3f> normalesV;
   vector <_vertex3f> centroides;
   vector <_vertex2i> cordtext;

};

#endif // O3D_H
