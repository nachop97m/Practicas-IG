#include "o3ds.h"

O3DS::O3DS()
{
}

O3DS::O3DS( vector <_vertex3f> &n_vertex){

    this->vertices.resize(n_vertex.size());

    for (unsigned int i=0; i < n_vertex.size(); i++){

        this->vertices[i].x = n_vertex[i].x;
        this->vertices[i].y = n_vertex[i].y;
        this->vertices[i].z = n_vertex[i].z;

    }

}

void O3DS::aniadirVertice(float x, float y, float z){

        vertices.resize(vertices.size()+1);

       _vertex3f vertice (x,y,z);

       this->vertices.push_back(vertice);

}

void O3DS::pintarVertices(){


    glColor3f(1,0,0);  // R G B

    glPointSize(8);

    glBegin(GL_POINTS);

        for (unsigned int i=0; i<vertices.size(); i++){

            glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);

        }

    glEnd();

}
