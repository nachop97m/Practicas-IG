#ifndef O3DS_H
#define O3DS_H

#include <GL/glew.h>
#include "vertex.h"
#include <vector>


class O3DS
{

public:
    O3DS();
    O3DS( vector <_vertex3f> & );
    void aniadirVertice(float, float, float);
    void pintarVertices();


protected:
   vector <_vertex3f> vertices;



};

#endif // O3DS_H
