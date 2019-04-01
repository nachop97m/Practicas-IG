#include "basemed.h"

baseMed::baseMed(int n, int np) : bsp (n, np)
{

    this->basemed.revolucion(np);

}

void baseMed::dibujar(int tipo, char mov){

    if (mov=='K' && pos1 < 17){

        pos1 += 0.3;
        pos2 += 0.3;

    }

    else if (mov=='J' && pos1 > 11.3){

        pos1 -= 0.3;
        pos2 -= 0.3;

    }

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,pos1,0);
    glScalef(3,1,2.5);
    this->basemed.dibujar(tipo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1, pos2,0);
    glScalef(0.2,8,0.2);
    this->basemed2.dibujar(tipo);
    glPopMatrix();
    glPushMatrix();
    bsp.dibujar(tipo,mov);
    glPopMatrix();

}
