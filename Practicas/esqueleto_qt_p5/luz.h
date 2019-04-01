#include "vertex.h"
#include <GL/glut.h>

#ifndef _LUZ
#define _LUZ

class Luz {

    private:

        GLenum id;
        bool direccional;

        GLfloat alfa;
        GLfloat beta;

    public:

        Luz();
        void activar();
        void desactivar();
        void setID(const GLenum &i);
        void setDireccional(const bool &d);
        void setPosicion(const _vertex3f &p);
        void setDireccion(const GLfloat &a, const GLfloat &b);
        void setAmbiental(const _vertex4f &a);
        void setDifuso(const _vertex4f &d);
        void setEspecular(const _vertex4f &e);
};

#endif
