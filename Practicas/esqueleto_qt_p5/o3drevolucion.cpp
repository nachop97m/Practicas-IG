#include "o3drevolucion.h"
#include <cmath>
#include <iostream>

O3DREVOLUCION::O3DREVOLUCION()
{

}

void O3DREVOLUCION::revolucion(int n_puntos = 6){

    int size = this->vertices.size();   // Tamaño vertices inicial (nº puntos iniciales)
    int total = size * n_puntos;                 // Total puntos tras barrido

    bool top = true, bottom = true;      // tapaderas


    if (this->vertices[0].x){

        //total -= n_puntos;      // No se realiza barrido de los vertices en el eje Y
        bottom = false;         // Abierto por abajo

    }

    if (this->vertices[size-1].x){

        //total -= n_puntos;      // No se realiza barrido de los vertices en el eje Y
        top = false;            // Abierto por arriba

    }


    float alpha = (2 * M_PI) / n_puntos;        // Angulo vertices
    this->vertices.resize(total);


    for (int i=0; i < n_puntos; i++){

        for (int c=0; c < size; c++){

            this->vertices[i*size + c].x = this->vertices[c].x * cos(alpha * i);    // Traslacion sobre eje Y
            this->vertices[i*size + c].y = this->vertices[c].y;
            this->vertices[i*size + c].z = this->vertices[c].x * sin(alpha * i);

        }

    }

    this->triangulos.resize(size * n_puntos * 2);
    int num = 0;

    if (bottom){            // Tapa inferior

        for (int j=0; j < n_puntos; j++){

            this->triangulos[num]._0 = (size * (j+1)) % total;
            this->triangulos[num]._1 = (size * (j+1) + 1) % total;
            this->triangulos[num]._2 = 1 + (size * j) % total;

            num++;
        }

    }

    if (top){               // Tapa superior

        for (int j=0; j < n_puntos; j++){

            this->triangulos[num]._0 = ((size - 2) + (size * j)) % total;
            this->triangulos[num]._1 = ((size - 2) + size * (j+1)) % total;
            this->triangulos[num]._2 = ((size - 1) + (size * j)) % total;

            num++;
        }


    }

    int i = 0;
    int fini = size - 1;

    if (bottom)     // Si hay tapa inferior, nos saltamos la primera fila de la matriz
        i++;

    if (top)        // Si hay tapa superior, nos saltamos la utlima fila de la matriz
        fini--;

    for (; i < fini; i++){

        for (int j=0; j < n_puntos; j++){

            this->triangulos[num]._0 = (size * j + i) % total;
            this->triangulos[num]._1 = (size * (j+1) + i) % total;
            this->triangulos[num]._2 = ((i + 1) + (size * j)) % total;

            this->triangulos[num+1]._0 = (size * (j+1) + i) % total;
            this->triangulos[num+1]._1 = (size * (j+1) + 1 +i) % total;
            this->triangulos[num+1]._2 = ((i + 1) + (size * j)) % total;

            num += 2;

        }

    }

    this->normalesTriangulos();
    this->normalesVertices();

}
