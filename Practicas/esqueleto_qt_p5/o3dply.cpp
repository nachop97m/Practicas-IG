#include "o3dply.h"

O3DPLY::O3DPLY()
{

    _file_ply File_ply;

    if (File_ply.open("/home/nacho/IG/Practicas/modelos_ply/beethoven.ply")){

        File_ply.read(this->vertices, this->triangulos);

    }

    this->normalesTriangulos();
    this->normalesVertices();

}
