#include "extremidad2.h"

extremidad2::extremidad2(int n, int np)
{
    this->cl.revolucion(np);
}

void extremidad2::dibujar(int tipo,char mov){

    if (mov == 'K' && alfa2 > -70){

       // alfa1++;
        alfa2 -= 2;

    }

    else if (mov == 'J' && alfa2 < 0){

       // alfa1--;
        alfa2 += 2;

    }

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(alfa2,0,0,1);
    glTranslatef(-2.5,0.4,0);
    glRotatef(80,0,0,1);
    glScalef(0.2,5,0.2);
    this->cl.dibujar(tipo);
    glPopMatrix();

}
