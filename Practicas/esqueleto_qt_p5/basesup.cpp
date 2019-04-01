#include "basesup.h"

baseSup::baseSup(int n, int np) : brz(n, np)
{
    this->basesup.revolucion(np);

}

void baseSup::dibujar(int tipo, char mov){

    if (mov == 'K' && alfa1 < 45){

        alfa1++;
        alfa1++;
        //alfa2 -= 2;

    }

    else if (mov == 'J' && alfa1 > 0){

        alfa1--;
        alfa1--;
       // alfa2 += 2;

    }

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,18,0);
    glScalef(3,1,2.5);
    this->basesup.dibujar(tipo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,18,0);
    //glRotatef(315,0,0,1);
    glRotatef(180,0,1,0);
    glRotatef(alfa1+45,0,0,1);
    glTranslatef(0,-5,0);
    brz.dibujar(tipo,mov);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,18,0);
   // glRotatef(45,0,0,1);
    glRotatef(alfa1+45,0,0,1);
    glTranslatef(0,-5,0);
    brz.dibujar(tipo,mov);
    glPopMatrix();

}
