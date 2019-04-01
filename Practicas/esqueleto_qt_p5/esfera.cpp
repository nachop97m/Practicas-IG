#include "esfera.h"

esfera::esfera(){


}

esfera::esfera(int np=5){

    this->vertices = {{0,-0.5,0}};

    this->vertices.resize(np);

    float alpha = (M_PI) / (np-1);

    for (int c=1; c < np; c++){

            this->vertices[c].x = this->vertices[0].y * sin(alpha * c);
            this->vertices[c].y = this->vertices[0].y * cos(alpha * c);
            this->vertices[c].z = this->vertices[0].z;

    }

}
