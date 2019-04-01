#include "brazo.h"

brazo::brazo(int n, int np) : ext(n, np), ext2(n, np)
{
    cl.revolucion(np);
}

void brazo::dibujar(int tipo,char mov){

    if (mov == 'K' && alfa1 < 45){

        alfa1++;

    }

    else if (mov == 'J' && alfa1 > 0){

        alfa1--;

    }

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    this->ext.dibujar(tipo);
    glPopMatrix();
    glPushMatrix();
    this->ext2.dibujar(tipo, mov);
    glPopMatrix();

}
