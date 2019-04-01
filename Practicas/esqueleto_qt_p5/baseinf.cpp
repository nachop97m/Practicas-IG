#include "baseinf.h"

baseInf::baseInf(int n, int np) : eje(n, np)
{

}

GLfloat baseInf::getDesp(){

    return desp;

}

void baseInf::setDesp(GLfloat dsp){

    this->desp = dsp;

}

void baseInf::dibujar(int tipo, char mov){

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,0.5,0);
    glScalef(8,1,8);
    this->basei.dibujar(tipo);
    glPopMatrix();
    glPushMatrix();
    glRotatef(desp,0,1,0);
    this->eje.dibujar(tipo, mov);
    glPopMatrix();

}
