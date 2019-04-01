#include "luz.h"

Luz::Luz() {

}

void Luz::activar() {

    const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat light_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_position[] = { 5.0f, 0.0f, 5.0f, 0.0f };

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

    glEnable(GL_LIGHTING);
    glEnable(id);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    if(direccional) {
        glRotatef(alfa,0,1,0);
        glRotatef(beta,1,0,0);
    }
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
    glDisable(GL_LIGHTING);
}

void Luz::desactivar() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glDisable(id);
    glPopMatrix();
}

void Luz::setID(const GLenum &i) {
    id = i;
}

void Luz::setDireccional(const bool &d) {
    if(d) {
        direccional = true;
        posicion[3] = 0;
    } else {
        direccional = false;
        posicion[3] = 1;
    }
}

void Luz::setPosicion(const _vertex3f &p) {
    posicion._0 = p._0;
    posicion._1 = p._1;
    posicion._2 = p._2;
}

void Luz::setDireccion(const GLfloat &a, const GLfloat &b) {
    alfa = a;
    beta = b;
}

void Luz::setAmbiental(const _vertex4f &a) {
    ambiental = a;
}

void Luz::setDifuso(const _vertex4f &d) {
    difusa = d;
}

void Luz::setEspecular(const _vertex4f &e) {
    especular = e;
}
