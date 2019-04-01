#include "o3d.h"

O3D::O3D(){




}

O3D::O3D(std::vector<_vertex3i>  & verticesTriangulo, std::vector<_vertex3f> & vertices){

    this->triangulos.resize(verticesTriangulo.size());

    for (int i =0;i<verticesTriangulo.size();i++){

            this->triangulos[i].x=verticesTriangulo[i].x;
            this->triangulos[i].y=verticesTriangulo[i].y;
            this->triangulos[i].z=verticesTriangulo[i].z;


    }

    this->vertices.resize(vertices.size());


    for(int i=0;i<vertices.size();i++){

        this->vertices[i].x=vertices[i].x;
        this->vertices[i].y=vertices[i].y;
        this->vertices[i].z=vertices[i].z;


    }









}


void O3D::generarNormalesTriangulos(){



    //Normales
    this->normalesTriangulos.resize(this->triangulos.size());

    for (int i =0;i< this->triangulos.size();i++){

        _vertex3f vectorA= this->vertices[triangulos[i].y] - this->vertices[triangulos[i].x];
        _vertex3f vectorB= this->vertices[triangulos[i].z] - this->vertices[triangulos[i].y];

        this->normalesTriangulos[i].x=vectorA.y * vectorB.z - (vectorA.z * vectorB.y);
        this->normalesTriangulos[i].y=vectorA.x * vectorB.z - (vectorA.z * vectorB.x);
        this->normalesTriangulos[i].z=vectorA.x * vectorB.y - (vectorA.y * vectorB.x);



        this->normalesTriangulos[i].normalize();


    }


}



void O3D::generarNormalesVertices(){


    int vertice1,vertice2,vertice3;

    std::vector<int> numeroTriangulos(vertices.size(),0);

    //resize y no reserve
    this->normalesVertices.resize(vertices.size());


    for (int i =0;i<normalesVertices.size();i++){
        normalesVertices[i].x=0.0;
        normalesVertices[i].y=0.0;
        normalesVertices[i].z=0.0;
    }


    for (int i=0;i<this->triangulos.size();i++){

        vertice1=this->triangulos[i].x;
        vertice2=this->triangulos[i].y;
        vertice3=this->triangulos[i].z;



        this->normalesVertices[vertice1].x += this->normalesTriangulos[i].x;
        this->normalesVertices[vertice1].y += this->normalesTriangulos[i].y;
        this->normalesVertices[vertice1].z += this->normalesTriangulos[i].z;
        numeroTriangulos[vertice1]++;


        this->normalesVertices[vertice2].x += this->normalesTriangulos[i].x;
        this->normalesVertices[vertice2].y += this->normalesTriangulos[i].y;
        this->normalesVertices[vertice2].z += this->normalesTriangulos[i].z;
        numeroTriangulos[vertice2]++;




        this->normalesVertices[vertice3].x += this->normalesTriangulos[i].x;
        this->normalesVertices[vertice3].y += this->normalesTriangulos[i].y;
        this->normalesVertices[vertice3].z += this->normalesTriangulos[i].z;
        numeroTriangulos[vertice3]++;




    }


    for (int i=0;i<normalesVertices.size();i++){

        normalesVertices[i].x = normalesVertices[i].x/numeroTriangulos[i];
        normalesVertices[i].y = normalesVertices[i].y/numeroTriangulos[i];
        normalesVertices[i].z = normalesVertices[i].z/numeroTriangulos[i];

        normalesVertices[i].normalize();
    }



}


void O3D::dibujarLineas(){

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0,0,1); 

    int vertice1,vertice2,vertice3;

    glBegin(GL_TRIANGLES);


        for (int i =0;i<this->triangulos.size();i++){

            vertice1=triangulos[i].x;
            vertice2=triangulos[i].y;
            vertice3=triangulos[i].z;

            glVertex3f(vertices[vertice1].x,vertices[vertice1].y,vertices[vertice1].z);
            glVertex3f(vertices[vertice2].x,vertices[vertice2].y,vertices[vertice2].z);
            glVertex3f(vertices[vertice3].x,vertices[vertice3].y,vertices[vertice3].z);


        }




    glEnd();



}


void O3D::dibujarCaras(){

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glColor3f(1,0.1,1);

    int vertice1,vertice2,vertice3;

    glBegin(GL_TRIANGLES);


        for (int i =0;i<this->triangulos.size();i++){

            vertice1=triangulos[i].x;
            vertice2=triangulos[i].y;
            vertice3=triangulos[i].z;

            glVertex3f(vertices[vertice1].x,vertices[vertice1].y,vertices[vertice1].z);
            glVertex3f(vertices[vertice2].x,vertices[vertice2].y,vertices[vertice2].z);
            glVertex3f(vertices[vertice3].x,vertices[vertice3].y,vertices[vertice3].z);


        }




    glEnd();




}

void O3D::ajedrez(){


    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    int vertice1,vertice2,vertice3;

    glBegin(GL_TRIANGLES);


        for (int i =0;i<this->triangulos.size();i++){

            vertice1=triangulos[i].x;
            vertice2=triangulos[i].y;
            vertice3=triangulos[i].z;

            if (i%2==0)
                glColor3f(1,0,0);
            else
                glColor3f(0,0,0);

            glVertex3f(vertices[vertice1].x,vertices[vertice1].y,vertices[vertice1].z);
            glVertex3f(vertices[vertice2].x,vertices[vertice2].y,vertices[vertice2].z);
            glVertex3f(vertices[vertice3].x,vertices[vertice3].y,vertices[vertice3].z);


        }




    glEnd();





}

void O3D::dibujar(char modo){


    if (modo=='p')
        this->dibujarPuntos();
    else if (modo =='l')
        this->dibujarLineas();
    else if (modo == 'c')
        this->ajedrez();
    else if (modo == 'f')
        this->dibujarCaras();
    else if (modo == 'T')
        this->sombreadoPlanoTextura();





}


void O3D::sombreadoPlano(char material,bool direccional,bool posicional,bool luz,double anguloX,double anguloY,double x, double y , double z){


    glPushMatrix();

    //LUZ------------------------------------------------------------------------
    if (luz){

        GLfloat Ambiente[4]={1,1,1,1};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT,Ambiente);

        //F4
        if (direccional){
            //girar con el glrotate
            //W == 0 --> Direccional (x,y,z)---> describen la direccion
            GLfloat Luz0[4]={-20,50,0,0};
            //GLfloat Ambiente[4]={1,1,1,1};
            //glLightModelfv(GL_LIGHT_MODEL_AMBIENT,Ambiente);
            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
            glRotatef(anguloX,1,0,0);
            glRotatef(anguloY,0,1,0);
            glLightfv(GL_LIGHT0,GL_POSITION,Luz0);
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);




        }
        if (posicional){

            //W == 1 -->Posicional (x,y,z)---->posicion de la luz
            GLfloat Luz1[4]={10+x,10+y,-10+z,1};
            //GLfloat Ambiente[4]={1,1,1,1};
            //glLightModelfv(GL_LIGHT_MODEL_AMBIENT,Ambiente);
            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
            glLightfv(GL_LIGHT1,GL_POSITION,Luz1);
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT1);
        }



    }


    glPopMatrix();


    glPushMatrix();

    //MATERIAL-----------------------------------------------------------------
    //Material oro
    if (material=='R'){


        GLfloat especular[4]={0.628281,0.555802,0.366065,0.4};
        GLfloat difuso[4]={0.75164,0.60648,0.22648,0.4};
        GLfloat ambiente[4]={0.24725,0.1995,0.0745,0.4};

        glMaterialfv(GL_FRONT,GL_AMBIENT,(GLfloat *) &ambiente);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,(GLfloat *) &difuso);
        glMaterialfv(GL_FRONT,GL_SPECULAR,(GLfloat *) &especular);
        glMaterialf(GL_FRONT,GL_SHININESS,10);


    }//Material rojo caucho
    else if (material == 'O'){



        GLfloat especular[4]={0.7,0.04,0.04,0.78125};
        GLfloat difuso[4]={0.5,0.4,0.4,0.78125};
        GLfloat ambiente[4]={0.05,0.0,0.0,0.78125};

        glMaterialfv(GL_FRONT,GL_AMBIENT,(GLfloat *) &ambiente);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,(GLfloat *) &difuso);
        glMaterialfv(GL_FRONT,GL_SPECULAR,(GLfloat *) &especular);
        glMaterialf(GL_FRONT,GL_SHININESS,10);


    //Ruby
    }else if (material=='B'){



        GLfloat especular[4]={0.727811,0.626959,0.626959,0.6};
        GLfloat difuso[4]={0.61424,0.04136,0.04136,0.6};
        GLfloat ambiente[4]={0.1745,0.01175,0.01175,0.6};

        glMaterialfv(GL_FRONT,GL_AMBIENT,(GLfloat *) &ambiente);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,(GLfloat *) &difuso);
        glMaterialfv(GL_FRONT,GL_SPECULAR,(GLfloat *) &especular);
        glMaterialf(GL_FRONT,GL_SHININESS,10);



    }

    glPopMatrix();



    glPushMatrix();

        glShadeModel(GL_FLAT);
        glMatrixMode(GL_MODELVIEW);
        glBegin(GL_TRIANGLES);
        for(unsigned int i=0;i< triangulos.size();i++){

            glNormal3f(normalesTriangulos[i].x, normalesTriangulos[i].y,normalesTriangulos[i].z);

            glVertex3f(vertices[triangulos[i].x].x, vertices[triangulos[i].x].y, vertices[triangulos[i].x].z);

            glVertex3f(vertices[triangulos[i].y].x, vertices[triangulos[i].y].y, vertices[triangulos[i].y].z);

            glVertex3f(vertices[triangulos[i].z].x, vertices[triangulos[i].z].y, vertices[triangulos[i].z].z);

        }



         glEnd();

         glDisable(GL_LIGHTING);

     glPopMatrix();



}


void O3D::sombreadoGouraud(char material,bool direccional,bool posicional,bool luz,double anguloX,double anguloY,double x, double y , double z){


    glPushMatrix();

    //LUZ------------------------------------------------------------------------
    if (luz){

        //F4
        if (direccional){
            //girar con el glrotate
            //W == 0 --> Direccional (x,y,z)---> describen la direccion
            GLfloat Luz0[4]={-20,50,0,0};
            GLfloat Ambiente[4]={1,1,1,1};
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT,Ambiente);
            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
            glRotatef(anguloX,1,0,0);
            glRotatef(anguloY,0,1,0);
            glLightfv(GL_LIGHT0,GL_POSITION,Luz0);
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);




        }else if (posicional){

            //W == 1 -->Posicional (x,y,z)---->posicion de la luz
            GLfloat Luz0[4]={10+x,10+y,-10+z,1};
            GLfloat Ambiente[4]={1,1,1,1};
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT,Ambiente);
            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
            glLightfv(GL_LIGHT0,GL_POSITION,Luz0);
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);


        }



    }


    glPopMatrix();









    glPushMatrix();

    if (material== 'R'){


        GLfloat especular[4]={0.628281,0.555802,0.366065,0.4};
        GLfloat difuso[4]={0.75164,0.60648,0.22648,0.4};
        GLfloat ambiente[4]={0.24725,0.1995,0.0745,0.4};

        glMaterialfv(GL_FRONT,GL_AMBIENT,(GLfloat *) &ambiente);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,(GLfloat *) &difuso);
        glMaterialfv(GL_FRONT,GL_SPECULAR,(GLfloat *) &especular);
        glMaterialf(GL_FRONT,GL_SHININESS,10);


    }
    else if (material == 'O'){



        GLfloat especular[4]={0.7,0.04,0.04,0.78125};
        GLfloat difuso[4]={0.5,0.4,0.4,0.78125};
        GLfloat ambiente[4]={0.05,0.0,0.0,0.78125};

        glMaterialfv(GL_FRONT,GL_AMBIENT,(GLfloat *) &ambiente);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,(GLfloat *) &difuso);
        glMaterialfv(GL_FRONT,GL_SPECULAR,(GLfloat *) &especular);
        glMaterialf(GL_FRONT,GL_SHININESS,10);



    }else if (material=='B'){



        GLfloat especular[4]={0.727811,0.626959,0.626959,0.6};
        GLfloat difuso[4]={0.61424,0.04136,0.04136,0.6};
        GLfloat ambiente[4]={0.1745,0.01175,0.01175,0.6};

        glMaterialfv(GL_FRONT,GL_AMBIENT,(GLfloat *) &ambiente);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,(GLfloat *) &difuso);
        glMaterialfv(GL_FRONT,GL_SPECULAR,(GLfloat *) &especular);
        glMaterialf(GL_FRONT,GL_SHININESS,10);



    }





    glPopMatrix();

    glPushMatrix();



    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glBegin(GL_TRIANGLES);
    for(unsigned int i=0;i< triangulos.size();i++){

        glNormal3f(normalesVertices[triangulos[i].x].x, normalesVertices[triangulos[i].x].y,normalesVertices[triangulos[i].x].z);
                glVertex3f(vertices[triangulos[i].x].x, vertices[triangulos[i].x].y, vertices[triangulos[i].x].z);





        glNormal3f(normalesVertices[triangulos[i].y].x, normalesVertices[triangulos[i].y].y,normalesVertices[triangulos[i].y].z);
                glVertex3f(vertices[triangulos[i].y].x, vertices[triangulos[i].y].y, vertices[triangulos[i].y].z);




        glNormal3f(normalesVertices[triangulos[i].z].x, normalesVertices[triangulos[i].z].y,normalesVertices[triangulos[i].z].z);
                glVertex3f(vertices[triangulos[i].z].x, vertices[triangulos[i].z].y, vertices[triangulos[i].z].z);

    }



    glEnd();

    glDisable(GL_LIGHTING);

    glPopMatrix();
}



void O3D::sombreadoPlanoTextura(){


    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);


    for (int i =0;i<this->vertices.size();i++){

        glTexCoord2f(parametricos[i].x,parametricos[i].y);
        glVertex3f(this->vertices[i].x,this->vertices[i].y,this->vertices[i].z);



    }



    glEnd();
    glDisable(GL_TEXTURE_2D);

     glPopMatrix();





}



void O3D::sombreadoPlanoTextura(std::vector<_vertex3f> puntos){

    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);


    for (int i =0;i<puntos.size();i++){

        glTexCoord2f(parametricos[i].x,parametricos[i].y);
        glVertex3f(puntos[i].x,puntos[i].y,puntos[i].z);



    }



    glEnd();
    glDisable(GL_TEXTURE_2D);

     glPopMatrix();



}

void O3D::generarParametricos(std::vector<_vertex2f> rango){


    this->parametricos.resize(this->vertices.size());


    //Asignacion de P0
    this->parametricos[0].x=rango[0].x;
    this->parametricos[0].y=rango[0].y;

    //P1
    this->parametricos[1].x=rango[1].x;
    this->parametricos[1].y=rango[0].y;

    //P2
    this->parametricos[2].x=rango[1].x;
    this->parametricos[2].y=rango[1].y;

    //P3
    this->parametricos[3].x=rango[0].x;
    this->parametricos[3].y=rango[1].y;








}



