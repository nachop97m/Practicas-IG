#include "o3drevolucion.h"
#include <cmath>

O3DREVOLUCION::O3DREVOLUCION()
{

}

void O3DREVOLUCION::revolucion(int n_puntos = 6){

    unsigned int size = this->vertices.size();
    int total = size * n_puntos;
    this->vertices.resize(total);
    bool top = true, bottom = true;      // tapaderas


    if (this->vertices[0].x)
        bottom = false;         // Abierto por abajo

    if (this->vertices[size-1].x)
        top = false;            // Abierto por arriba


    float alpha = (2 * M_PI) / n_puntos;

    for (int i=0; i < n_puntos; i++){

        for (int c=0; c < size; c++){

            this->vertices[i*size + c].x = this->vertices[c].x * cos(alpha * i);
            this->vertices[i*size + c].y = this->vertices[c].y;
            this->vertices[i*size + c].z = this->vertices[c].x * sin(alpha * i);

        }

    }

    this->triangulos.resize((size * n_puntos * 2) - (n_puntos*2));
    int num = 0;

    if (bottom){

        for (int j=0; j < n_puntos; j++){

            this->triangulos[num]._0 = (size * (j+1)) % total;
            this->triangulos[num]._1 = (size * (j+1) + 1) % total;
            this->triangulos[num]._2 = 1 + (size * j) % total;

            num++;
        }

    }

    if (top){

        for (int j=0; j < n_puntos; j++){

            this->triangulos[num]._0 = ((size - 2) + (size * j)) % total;
            this->triangulos[num]._1 = ((size - 2) + size * (j+1)) % total;
            this->triangulos[num]._2 = ((size - 1) + (size * j)) % total;

            num++;
        }


    }

    int i = 0, j = 0;
    int fini = size - 1;

    if (bottom)
        i++;

    if (top)
        fini--;

    for (; i < fini; i++){

        for (; j < n_puntos; j++){

            this->triangulos[num]._0 = (size * j + i) % total;
            this->triangulos[num]._1 = (size * (j+1) + i) % total;
            this->triangulos[num]._2 = ((i + 1) + (size * j)) % total;

            this->triangulos[num+1]._0 = (size * (j+1) + i) % total;
            this->triangulos[num+1]._1 = (size * (j+1) + 1 +i) % total;
            this->triangulos[num+1]._2 = ((i + 1) + (size * j)) % total;

            num += 2;

        }


    }


}

