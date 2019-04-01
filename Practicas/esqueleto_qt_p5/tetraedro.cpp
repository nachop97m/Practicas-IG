#include "tetraedro.h"

tetraedro::tetraedro()
{

    this->vertices = {{-0.5,-0.5,0.5},{0.5,-0.5,0.5},
                 {0,-0.5,-0.5},{0,0.5,0}};
    this->triangulos = {{0,1,2},{2,3,1},{3,0,2},{0,1,3}};

}
