#include "o3d.h"

O3D::O3D()
{

}

O3D::O3D( vector <_vertex3i> & indices, vector <_vertex3f> puntos){

    this->triangulos.resize(indices.size());
    this->vertices.resize(puntos.size());

    for (unsigned int i=0; i < indices.size(); i++){

        this->triangulos[i].x = indices[i].x;
        this->triangulos[i].y = indices[i].y;
        this->triangulos[i].z = indices[i].z;

    }

    for (unsigned int i=0; i < puntos.size(); i++){

        this->vertices[i].x = puntos[i].x;
        this->vertices[i].y = puntos[i].y;
        this->vertices[i].z = puntos[i].z;

    }

    this->normalesTriangulos();
    this->normalesVertices();

}

void O3D::normalesTriangulos(){

    this->normalesT.resize(this->triangulos.size());
    this->centroides.resize(this->triangulos.size());
    _vertex3f P, Q, N;
    float aux;

    for (unsigned int i=0; i < this->triangulos.size(); i++){

        P.x = this->vertices[this->triangulos[i].y].x - this->vertices[this->triangulos[i].x].x;
        P.y = this->vertices[this->triangulos[i].y].y - this->vertices[this->triangulos[i].x].y;
        P.z = this->vertices[this->triangulos[i].y].z - this->vertices[this->triangulos[i].x].z;

        Q.x = this->vertices[this->triangulos[i].z].x - this->vertices[this->triangulos[i].x].x;
        Q.y = this->vertices[this->triangulos[i].z].y - this->vertices[this->triangulos[i].x].y;
        Q.z = this->vertices[this->triangulos[i].z].z - this->vertices[this->triangulos[i].x].z;

        N.x = P.y * Q.z - P.z * Q.y;
        N.y = P.z * Q.x - P.x * Q.z;
        N.z = P.x * Q.y - P.y * Q.x;

        N.normalize();

        //Comprobar si la normal va hacia dentro

        aux=0;

        aux += N.x * (this->vertices[this->triangulos[i].x].x) + N.y * (this->vertices[this->triangulos[i].x].y) + N.z * (this->vertices[this->triangulos[i].x].z);

        if (aux < 0){

            N.x = -N.x;
            N.y = -N.y;
            N.z = -N.z;

        }

        this->normalesT[i] = N;

        // solo para dibujar las normales
        this->centroides[i].x = (this->vertices[this->triangulos[i].x].x + this->vertices[this->triangulos[i].y].x + this->vertices[this->triangulos[i].z].x) / 3;
        this->centroides[i].y = (this->vertices[this->triangulos[i].x].y + this->vertices[this->triangulos[i].y].y + this->vertices[this->triangulos[i].z].y) / 3;
        this->centroides[i].z = (this->vertices[this->triangulos[i].x].z + this->vertices[this->triangulos[i].y].z + this->vertices[this->triangulos[i].z].z) / 3;

    }

}

void O3D::normalesVertices(){

    int v;
    vector <int> medias (this->vertices.size(),0);
    this->normalesV.resize(this->vertices.size());

    float aux;


    for (unsigned int i=0; i < this->normalesV.size(); i++){

        this->normalesV[i].x = 0;
        this->normalesV[i].y = 0;
        this->normalesV[i].z = 0;

    }

    for (unsigned int i=0; i < this->triangulos.size(); i++){

        v = this->triangulos[i].x;
        this->normalesV[v].x += this->normalesT[i].x;
        this->normalesV[v].y += this->normalesT[i].y;
        this->normalesV[v].z += this->normalesT[i].z;
        medias[v]++;

        v = this->triangulos[i].y;
        this->normalesV[v].x += this->normalesT[i].x;
        this->normalesV[v].y += this->normalesT[i].y;
        this->normalesV[v].z += this->normalesT[i].z;
        medias[v]++;

        v = this->triangulos[i].z;
        this->normalesV[v].x += this->normalesT[i].x;
        this->normalesV[v].y += this->normalesT[i].y;
        this->normalesV[v].z += this->normalesT[i].z;
        medias[v]++;

    }

    for (unsigned int i=0; i < this->normalesV.size(); i++){

        this->normalesV[i].x /= medias[i];
        this->normalesV[i].y /= medias[i];
        this->normalesV[i].z /= medias[i];

        this->normalesV[i].normalize();

    }

}

void O3D::suavizado_plano(bool l, bool l1, bool l2, float a, float b, float c, float d, GLfloat alfa, GLfloat beta, int cont){

    // componentes de las luces
    GLfloat light_ambient[] = { 1, 1, 1, 1};
    GLfloat light_position[] = { a, b, c, d};
    GLfloat light_position2[] = { -20, 50, 0, 0};

    GLfloat light_ambient2[] = { 1, 1, 1, 1};
    GLfloat light_diffuse2[] = { 1, 1, 1, 1};
    GLfloat light_specular2[] = { 1, 1, 1, 1};

    if (l){

        glPushMatrix();

        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);

        // Posicional
        if (l1){

            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
            glLightfv(GL_LIGHT0, GL_POSITION, light_position);

            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);

        }

        else {

            glDisable(GL_LIGHT0);

        }

        //Direccional
        if(l2){

            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

            glRotatef(alfa,1,0,0);
            glRotatef(beta,0,1,0);

            glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
            glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient2);
            glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
            glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular2);

            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT1);


        }

        else {

            glDisable(GL_LIGHT1);
        }

        glPopMatrix();

    }

    glPushMatrix();

    // material 1 oro
    if (cont==0){

        GLfloat mat_ambient3[] = { 	0.24725, 0.1995, 0.0745,0.4};
        GLfloat mat_diffuse3[] = { 0.75164, 0.60648, 0.22648, 0.4};
        GLfloat mat_specular3[] = {0.628281,0.555802,0.366065,0.4};
        GLfloat high_shininess3[] = { 10 };

        glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient3);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse3);
        glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular3);
        glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess3);


    }

    // material 2 cromo
    else if(cont == 1){

        GLfloat mat_ambient2[] = { 0.25, 0.25,0.25,0.6};
        GLfloat mat_diffuse2[] = { 0.4, 0.4, 0.4, 0.6};
        GLfloat mat_specular2[] = {0.774597, 0.774597, 0.774597,0.6};
        GLfloat high_shininess2[] = { 10 };

        glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient2);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse2);
        glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular2);
        glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess2);

    }

    // material 3 obsidiana
    else{

        GLfloat mat_ambient[] = { 0.05375,0.05,0.06625, 0.3};
        GLfloat mat_diffuse[] = { 0.18275, 0.17, 0.22525, 0.3};
        GLfloat mat_specular[] = {0.332741, 0.328634, 0.346435, 0.3};
        GLfloat high_shininess[] = { 10 };

        glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
        glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
        glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess);


    }

    glPopMatrix();

    glPushMatrix();

   // glPolygonMode(GL_FRONT,GL_FILL);
    glShadeModel(GL_FLAT);

    glMatrixMode(GL_MODELVIEW);

    glBegin(GL_TRIANGLES);

    for(unsigned int i=0; i < this->triangulos.size(); i++){

        glNormal3f(this->normalesT[i].x, this->normalesT[i].y, this->normalesT[i].z);

        glVertex3f(this->vertices[this->triangulos[i].x].x, this->vertices[this->triangulos[i].x].y, this->vertices[this->triangulos[i].x].z);

        glVertex3f(this->vertices[this->triangulos[i].y].x, this->vertices[this->triangulos[i].y].y, this->vertices[this->triangulos[i].y].z);

        glVertex3f(this->vertices[this->triangulos[i].z].x, this->vertices[this->triangulos[i].z].y, this->vertices[this->triangulos[i].z].z);

    }

    glEnd();

    glDisable(GL_LIGHTING);

    glPopMatrix();

}

void O3D::suavizado_gouraud(bool l, bool l1, bool l2, float a, float b, float c, float d, GLfloat alfa, GLfloat beta, int cont){

    GLfloat light_ambient[] = { 1, 1, 1, 1};
    GLfloat light_position[] = { a, b, c, d};
    GLfloat light_position2[] = { -20, 50, 0, 0};

    GLfloat light_ambient2[] = { 1, 1, 1, 1};
    GLfloat light_diffuse2[] = { 1, 1, 1, 1};
    GLfloat light_specular2[] = { 1, 1, 1, 1};

    if (l){

        glPushMatrix();

        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);

        if (l1){

            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
            glLightfv(GL_LIGHT0, GL_POSITION, light_position);

            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);

        }

        else {

            glDisable(GL_LIGHT0);

        }


        if(l2){

            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

            glRotatef(alfa,1,0,0);
            glRotatef(beta,0,1,0);

            glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
            glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient2);
            glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
            glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular2);

            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT1);


        }

        else {

            glDisable(GL_LIGHT1);
        }

    }

    glPushMatrix();

    if (cont==0){

        GLfloat mat_ambient3[] = { 	0.24725, 0.1995, 0.0745,0.4};
        GLfloat mat_diffuse3[] = { 0.75164, 0.60648, 0.22648, 0.4};
        GLfloat mat_specular3[] = {0.628281,0.555802,0.366065,0.4};
        GLfloat high_shininess3[] = { 10 };

        glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient3);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse3);
        glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular3);
        glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess3);


    }

    else if(cont == 1){

        GLfloat mat_ambient2[] = { 0.25, 0.25,0.25,0.6};
        GLfloat mat_diffuse2[] = { 0.4, 0.4, 0.4, 0.6};
        GLfloat mat_specular2[] = {0.774597, 0.774597, 0.774597,0.6};
        GLfloat high_shininess2[] = { 10 };

        glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient2);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse2);
        glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular2);
        glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess2);

    }

    else{

        GLfloat mat_ambient[] = { 0.05375,0.05,0.06625, 0.3};
        GLfloat mat_diffuse[] = { 0.18275, 0.17, 0.22525, 0.3};
        GLfloat mat_specular[] = {0.332741, 0.328634, 0.346435, 0.3};
        GLfloat high_shininess[] = { 10 };

        glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
        glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
        glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess);


    }

    glPopMatrix();

    glPushMatrix();

   // glPolygonMode(GL_FRONT,GL_FILL);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_MODELVIEW);

    glBegin(GL_TRIANGLES);

    for(unsigned int i=0; i < this->triangulos.size(); i++){

        glNormal3f(this->normalesV[this->triangulos[i].x].x, this->normalesV[this->triangulos[i].x].y, this->normalesV[this->triangulos[i].x].z);

        glVertex3f(this->vertices[this->triangulos[i].x].x, this->vertices[this->triangulos[i].x].y, this->vertices[this->triangulos[i].x].z);


        glNormal3f(this->normalesV[this->triangulos[i].y].x, this->normalesV[this->triangulos[i].y].y, this->normalesV[this->triangulos[i].y].z);

        glVertex3f(this->vertices[this->triangulos[i].y].x, this->vertices[this->triangulos[i].y].y, this->vertices[this->triangulos[i].y].z);


        glNormal3f(this->normalesV[this->triangulos[i].z].x, this->normalesV[this->triangulos[i].z].y, this->normalesV[this->triangulos[i].z].z);

        glVertex3f(this->vertices[this->triangulos[i].z].x, this->vertices[this->triangulos[i].z].y, this->vertices[this->triangulos[i].z].z);

    }

    glEnd();

    glDisable(GL_LIGHTING);

    glPopMatrix();

}

void O3D::textura(double a, double b, int modo){

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);

    // opcion a
    if (modo == 0){


        glTexCoord2f(a,a);
        glVertex3f(this->vertices[79].x,this->vertices[79].y,this->vertices[79].z);

        glTexCoord2f(b,a);
        glVertex3f(this->vertices[70].x,this->vertices[70].y,this->vertices[70].z);

        glTexCoord2f(b,b);
        glVertex3f(this->vertices[0].x,this->vertices[0].y,this->vertices[0].z);

        glTexCoord2f(a,b);
        glVertex3f(this->vertices[9].x,this->vertices[9].y,this->vertices[9].z);
    }

    // opcion b
    else if (modo == 1){

        glTexCoord2f(a,a);
        glVertex3f(this->vertices[45].x,this->vertices[45].y,this->vertices[45].z);

        glTexCoord2f(b,a);
        glVertex3f(this->vertices[44].x,this->vertices[44].y,this->vertices[44].z);

        glTexCoord2f(b,b);
        glVertex3f(this->vertices[34].x,this->vertices[34].y,this->vertices[34].z);

        glTexCoord2f(a,b);
        glVertex3f(this->vertices[35].x,this->vertices[35].y,this->vertices[35].z);

    }

    // opcion c
    else if(modo == 2) {

        glTexCoord2f(a,a);
        glVertex3f(this->vertices[78].x,this->vertices[78].y,this->vertices[78].z);

        glTexCoord2f(b,a);
        glVertex3f(this->vertices[71].x,this->vertices[71].y,this->vertices[71].z);

        glTexCoord2f(b,b);
        glVertex3f(this->vertices[41].x,this->vertices[41].y,this->vertices[41].z);

        glTexCoord2f(a,b);
        glVertex3f(this->vertices[48].x,this->vertices[48].y,this->vertices[48].z);

    }

    // opcion d
    else {

        glTexCoord2f(0.25,0.25);
        glVertex3f(this->vertices[74].x,this->vertices[74].y,this->vertices[74].z);

        glTexCoord2f(0.75,0.25);
        glVertex3f(this->vertices[70].x,this->vertices[70].y,this->vertices[70].z);

        glTexCoord2f(0.75,0.75);
        glVertex3f(this->vertices[40].x,this->vertices[40].y,this->vertices[40].z);

        glTexCoord2f(0.25,0.75);
        glVertex3f(this->vertices[44].x,this->vertices[44].y,this->vertices[44].z);

    }
/*
    glTexCoord2f(a,a);
    glVertex3f(this->vertices[0].x,this->vertices[0].y,this->vertices[0].z);

    glTexCoord2f(b,a);
    glVertex3f(this->vertices[1].x,this->vertices[1].y,this->vertices[1].z);

    glTexCoord2f(b,b);
    glVertex3f(this->vertices[2].x,this->vertices[2].y,this->vertices[2].z);

    glTexCoord2f(a,b);
    glVertex3f(this->vertices[3].x,this->vertices[3].y,this->vertices[3].z);
*/
    glEnd();
    glDisable(GL_TEXTURE_2D);


    glPopMatrix();

}

void O3D::aniadirVertice(int a, int b, int c, float x, float y, float z){

    this->vertices.resize(vertices.size()+1);
    this->triangulos.resize(triangulos.size()+1);

   _vertex3f vertice (x,y,z);
   _vertex3i punto (a, b, c);

   this->vertices.push_back(vertice);
   this->triangulos.push_back(punto);

}

void O3D::pintarLineas(){

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // modo de rasterizacion
                                               // Poligonos con 2 caras

    glColor3f(0,0,1);

    glLineWidth(3);

    glBegin(GL_TRIANGLES);

    int a,b,c;

        for (unsigned int i=0; i<triangulos.size(); i++){

            // Obtengo los triangulos
            a = triangulos[i].x;
            b = triangulos[i].y;
            c = triangulos[i].z;

            // Dibujo los vertices del triangulo
            glVertex3f(vertices[a].x, vertices[a].y, vertices[a].z);
            glVertex3f(vertices[b].x, vertices[b].y, vertices[b].z);
            glVertex3f(vertices[c].x, vertices[c].y, vertices[c].z);

        }

    glEnd();


}

void O3D::pintarCarass(){

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // modo de rasterizacion
                                               // Poligonos con 2 caras

    glColor3f(0.5,1,0.2);

    glBegin(GL_TRIANGLES);

    int a,b,c;

        for (unsigned int i=0; i<triangulos.size(); i++){

            // Obtengo los triangulos
            a = triangulos[i].x;
            b = triangulos[i].y;
            c = triangulos[i].z;

            // Dibujo los vertices del triangulo
            glVertex3f(vertices[a].x, vertices[a].y, vertices[a].z);
            glVertex3f(vertices[b].x, vertices[b].y, vertices[b].z);
            glVertex3f(vertices[c].x, vertices[c].y, vertices[c].z);

        }

    glEnd();

}

void O3D::pintarAjedrez(){

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // modo de rasterizacion
                                               // Poligonos con 2 caras
    glBegin(GL_TRIANGLES);

    int a,b,c;

        for (unsigned int i=0; i<triangulos.size(); i++){

            // Obtengo los triangulos
            a = triangulos[i].x;
            b = triangulos[i].y;
            c = triangulos[i].z;

            if (i%2){

                glColor3f(0,0,0);

            }

            else{

                glColor3f(1,1,0);

            }

            // Dibujo los vertices del triangulo
            glVertex3f(vertices[a].x, vertices[a].y, vertices[a].z);
            glVertex3f(vertices[b].x, vertices[b].y, vertices[b].z);
            glVertex3f(vertices[c].x, vertices[c].y, vertices[c].z);

        }

    glEnd();

}

void O3D::dibujar(int tipo){

    switch (tipo){

    case (0):
      this->pintarVertices();
      break;

    case (1):
      this->pintarLineas();
      break;

    case(2):
      this->pintarCarass();
      break;

    case (3):
      this->pintarAjedrez();
      break;


    }
}
