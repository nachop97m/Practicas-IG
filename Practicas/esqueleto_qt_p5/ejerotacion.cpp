#include "ejerotacion.h"

ejeRotacion::ejeRotacion(int n, int np) : bsm(n, np)
{

    this->eje.revolucion(np);

}

void ejeRotacion::dibujar(int tipo, char mov){

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0, 9, 0);
    glScalef(0.5,18,0.5);
    this->eje.dibujar(tipo);
    glPopMatrix();
    glPushMatrix();
    bsm.dibujar(tipo,mov);
    glPopMatrix();

}
