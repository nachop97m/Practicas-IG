#include "tablero.h"

tablero::tablero(int a, int b)
{
    this->vertices.resize(a*b);
    this->triangulos.resize(a*b*2);

    // calcular las posiciones iniciales segun el numero de puntos
    float x_ini = -((b-1.0)/2.0);
    float y_ini = ((a-1.0)/2.0);
    float x_aux = x_ini;
    float y_aux = y_ini;


    _vertex3i indices;
    _vertex3f puntos;

    // vamos rellenando el vector de vertices a partir del primero
    for (int i=0; i < a; i++){

        for (int j=0; j < b; j++){

            puntos.x = x_aux;
            puntos.y = y_aux;
            puntos.z = 0.0;

            this->vertices.push_back(puntos);


            x_aux = x_aux + 1.0; // salto de columna

        }

        y_aux = y_aux - 1.0; // salto de linea
        x_aux = x_ini;

    }


    /* Los vertices se guardan en la segunda mitad del vector; se pasan a la primera mitad
     * para simplificar calculos posteriores
     */
    for (int i=this->vertices.size()/2, c=0; i < this->vertices.size(); c++, i++){

        this->vertices[c].x = this->vertices[i].x;
        this->vertices[c].y = this->vertices[i].y;
        this->vertices[c].z = this->vertices[i].z;

    }
/*

    this->vertices = {{-0.5,-0.5,0.0},{0.5,-0.5,0.0},{0.5,0.5,0.0},
                       {-0.5,0.5,0.0}};
    this->triangulos = {{0,1,2},{0,2,3}};

*/

}

void tablero::imagen(int a, int b, int c, int d, bool t){

    // carga de una imagen
    if (Imagen.load("/home/nacho/IG/Practicas/esqueleto_qt_p5/imagen.png")==false) cout << "Image not loaded" << endl;
    // reflejo vertical
    Imagen=Imagen.mirrored(false,true);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // parametros de aplicacion de la textura
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    // asignacion de la textura
    glTexImage2D(GL_TEXTURE_2D,0,4,Imagen.width(),Imagen.height(),0,GL_BGRA,GL_UNSIGNED_BYTE,Imagen.bits());

}
