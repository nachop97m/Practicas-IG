#include "extremidad.h"

extremidad::extremidad(int n, int np) : es(n)
{
    this->es.revolucion(np);
    this->ext.revolucion(np);
}

void extremidad::dibujar(int tipo){

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(0.4,10,0.4);
    this->ext.dibujar(tipo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,-5,0);
    //glScalef(0.2,0.2,0.2);
    glScalef(2.5,2.5,2.5);
    //this->bet.dibujar(tipo);
    this->es.dibujar(tipo);
    glPopMatrix();

}
