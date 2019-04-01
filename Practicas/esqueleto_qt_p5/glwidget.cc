//**************************************************************************
//
// Domingo Martin Perandres© 2014-2017
// http://calipso.ugr.es/dmartin
// dmartin@ugr.es
//
// GPL
//**************************************************************************

#include "glwidget.h"
#include <QPainter>
#include <QPaintEngine>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QCoreApplication>
#include <math.h>
#include <o3ds.h>
#include <o3d.h>

#include "window.h"
#include "o3ds.h"
#include "o3d.h"
#include "o3dply.h"
#include "cubo.h"
#include "tetraedro.h"
#include "o3drevolucion.h"
#include "cilindro.h"
#include "vaso.h"
#include "vaso_inv.h"
#include "tubo.h"
#include "cono.h"
#include "peon.h"
#include "esfera.h"
#include "baseinf.h"
#include "time.h"
#include "tablero.h"


using namespace std;
using namespace _gl_widget_ne;

char f;
bool pt=false, li=false, ca=false, aj=false, m=false,luz = false, luz1=false, luz2=false, textura=false, tex_cord=false, pts=true;
float a=20, b=50, c=0, d=0;
int cont2=0;
int modo=0;
double xt=0, yt=1;
GLfloat alfa, beta;
char gou = '-';
char mov = '-';
int aumentos = 0;
float acel = 0;
float desp;
baseInf watt (20,20);

void _gl_widget::rotar (){

    if (m){

        desp = watt.getDesp();

        if (mov == 'K' && acel < 0.013){

            acel += 0.0002;
            mov = '-';

        }

        else if (mov == 'J' && acel>0){

            acel -= 0.0002;
            mov = '-';

        }

        desp = (desp + 0.001) + acel;

        if (desp > 360.0)
            desp = 0;

    }

}

void _gl_widget::updt(){

        watt.setDesp(desp);
        repaint();

}

_gl_widget::_gl_widget(_window *Window1):Window(Window1)
{
  setMinimumSize(300, 300);
  setFocusPolicy(Qt::StrongFocus);

}

//*************************************************************************
//
//*************************************************************************

void _gl_widget::keyPressEvent(QKeyEvent *Keyevent)
{
  mov='-';

  switch(Keyevent->key()){
  case Qt::Key_Left:Observer_angle_y-=ANGLE_STEP;break;
  case Qt::Key_Right:Observer_angle_y+=ANGLE_STEP;break;
  case Qt::Key_Up:Observer_angle_x-=ANGLE_STEP;break;
  case Qt::Key_Down:Observer_angle_x+=ANGLE_STEP;break;
  case Qt::Key_PageUp:Observer_distance*=1.2;break;
  case Qt::Key_PageDown:Observer_distance/=1.2;break;

  case Qt::Key_1:f='T'; break;
  case Qt::Key_2:f='C'; break;
  case Qt::Key_3:f='Y'; break;
  case Qt::Key_4:f='R'; break;
  case Qt::Key_5:f='J'; break;
  case Qt::Key_6:f='O'; break;
  case Qt::Key_7:f='X'; break;

  case Qt::Key_X:
      if(aumentos<11){
          aumentos++;
          mov='K';
          watt.dibujar(20,mov);
      }
          break;
  case Qt::Key_Z:mov='J'; if (aumentos>0)aumentos--;break;
  case Qt::Key_M:if(m) m=false; else m=true; break;

  case Qt::Key_P:

      if (pt){

          pt=false;

      }

      else{

          pt=true;

      }

      gou = '-';

      break;


  case Qt::Key_L:

      if (li){

          li=false;

      }

      else{

          li=true;

      }

      gou = '-';

      break;

  case Qt::Key_F:

      if (!ca && aj){

          ca=true;
          aj=false;

      }

      else if (ca){

          ca=false;

      }

      else{

          ca=true;

      }

      gou = '-';

      break;

  case Qt::Key_C:

      if (!aj && ca){

          aj=true;
          ca=false;


      }

      else if(aj){

          aj=false;

      }

      else{

          aj=true;

      }

      gou = '-';

      break;

  case Qt::Key_S:

     if(gou == '-'){

          gou = 'p';
          pt=false, li=false, ca=false, aj=false;


      }

      else if (gou == 'p'){

          gou = 'g';

      }

     else if(gou == 'g'){

        gou = '-';

     }

    break;

  case Qt::Key_O:

      if (!luz){

          luz=true;

      }

      else{

          luz=false;

      }

      break;


  case Qt::Key_I:

      if (!luz1){

          luz1=true;

      }

      else{

          luz1=false;

      }

      break;

  case Qt::Key_U:

      if (!luz2){

          luz2=true;
      }

      else{

          luz2=false;

      }

      break;

  case Qt::Key_Y:

      cont2++;

      if (cont2>2)
          cont2=0;


      break;


    case Qt::Key_F1:

        a = a + 2;

        break;

    case Qt::Key_F2:

        b = b + 2;

        break;

    case Qt::Key_F3:

        c = c + 2;

        break;

    case Qt::Key_F4:

        a = a - 2;

        break;

    case Qt::Key_F5:

        b = b - 2;

        break;

    case Qt::Key_F6:

        c = c - 2;

        break;

    case Qt::Key_F7:

        alfa = alfa + 2;

        if (alfa > 360)
            alfa = 0;


        break;

    case Qt::Key_F8:

        alfa = alfa - 2;

        if (alfa < -360)
            alfa = 0;

        break;

    case Qt::Key_F9:

        beta = beta + 2;

        if (beta > 360)
            beta = 0;

        break;

    case Qt::Key_F10:

        beta = beta - 2;

        if (beta < -360)
            beta = 0;

        break;

  case Qt::Key_T:

    if(!textura)
        textura=true;

    else
        textura=false;

    break;

  case Qt::Key_N:

      if (!tex_cord){

         xt=0.25;
         yt=0.75;
         tex_cord=true;

      }

      else{

          xt=0;
          yt=1;
          tex_cord=false;

      }

    break;

  case Qt::Key_B:

      modo = (modo+1) % 4;

    break;

  case Qt::Key_A:

      if(pts){

          pts=false;
      }

      else{

          pts=true;
      }

    break;

  }


    update();

}

//**************************************************************************
//
//***************************************************************************

void _gl_widget::clear_window()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void _gl_widget::change_projection()
{
    const GLfloat aumento = GLfloat(windheight) / GLfloat (windwidth);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
  //  Front_plane>0  Back_plane>PlanoDelantero)
  glFrustum(X_MIN,X_MAX,Y_MIN*aumento,Y_MAX*aumento,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void _gl_widget::change_observer()
{
  // posicion del observador
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-Observer_distance);
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void _gl_widget::draw_axis()
{
  glBegin(GL_LINES);
  // eje X, color rojo
  glColor3f(1,0,0);
  glVertex3f(-AXIS_SIZE,0,0);
  glVertex3f(AXIS_SIZE,0,0);
  // eje Y, color verde
  glColor3f(0,1,0);
  glVertex3f(0,-AXIS_SIZE,0);
  glVertex3f(0,AXIS_SIZE,0);
  // eje Z, color azul
  glColor3f(0,0,1);
  glVertex3f(0,0,-AXIS_SIZE);
  glVertex3f(0,0,AXIS_SIZE);
  glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void _gl_widget::draw_objects()
{

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rotar()));
    timer->start(0.1);

    QTimer *timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(updt()));
    timer2->start(0.5);

    tetraedro tt;
    cubo cb;
    O3DPLY objply;
    tubo tb;
    esfera es (40);
    tablero tabx(8,10);


    es.revolucion(50);

    if (f == 'C'){

        if(pt)
            cb.pintarVertices();

        if(li)
            cb.pintarLineas();

        if(ca)
            cb.pintarCarass();

        if (aj)
            cb.pintarAjedrez();

    }

    else if (f == 'T'){

        if(pt)
            tt.pintarVertices();

        if(li)
            tt.pintarLineas();

        if(ca)
            tt.pintarCarass();

        if (aj)
            tt.pintarAjedrez();

    }

    else if(f == 'Y'){

        if(pt)
            objply.pintarVertices();

        if(li)
            objply.pintarLineas();

        if(ca)
            objply.pintarCarass();

        if (aj)
            objply.pintarAjedrez();

        if (gou == 'p'){

            objply.suavizado_plano(luz, luz1, luz2, a, b, c, d, alfa, beta, cont2);

        }

        if (gou == 'g'){

            objply.suavizado_gouraud(luz, luz1, luz2, a, b, c, d, alfa, beta, cont2);

        }

    }

    else if(f == 'R'){

        if(pt)
            es.pintarVertices();

        if(li)
            es.pintarLineas();

        if(ca)
            es.pintarCarass();

        if (aj)
            es.pintarAjedrez();

        if (gou == 'p'){

            es.suavizado_plano(luz, luz1, luz2, a, b, c, d, alfa, beta,cont2);

        }

        if (gou == 'g'){

            es.suavizado_gouraud(luz, luz1, luz2, a, b, c, d, alfa, beta,cont2);

        }

    }

    else if(f == 'J'){

        if(pt)
            watt.dibujar(0, mov);

        if(li)
            watt.dibujar(1, mov);

        if(ca)
            watt.dibujar(2, mov);

        if (aj)
            watt.dibujar(3, mov);

    }

    else if (f == 'X'){

        if (pts)
        tabx.pintarVertices();

        tabx.imagen(0,0,0,0, textura);
        tabx.textura(xt,yt, modo);


    }

}


//*************************************************************************
//
//*************************************************************************

void _gl_widget::paintGL()
{
  clear_window();
  change_projection();
  change_observer();
  draw_axis();
  draw_objects();
}

//*************************************************************************
//
//*************************************************************************

void _gl_widget::resizeGL(int Width1, int Height1)
{
  glViewport(0,0,Width1,Height1);
  windheight = Height1;
  windwidth = Width1;
}


//*************************************************************************
//
//*************************************************************************

void _gl_widget::initializeGL()
{
  const GLubyte* strm;

  strm = glGetString(GL_VENDOR);
  std::cerr << "Vendor: " << strm << "\n";
  strm = glGetString(GL_RENDERER);
  std::cerr << "Renderer: " << strm << "\n";
  strm = glGetString(GL_VERSION);
  std::cerr << "OpenGL Version: " << strm << "\n";

  if (strm[0] == '1'){
    std::cerr << "Only OpenGL 1.X supported!\n";
    exit(-1);
    }

  strm = glGetString(GL_SHADING_LANGUAGE_VERSION);
  std::cerr << "GLSL Version: " << strm << "\n";

  glewExperimental = GL_TRUE;
  int err = glewInit();
  if (GLEW_OK != err){
    std::cerr << "Error: " << glewGetErrorString(err) << "\n";
    exit (-1);
    }

  int Max_texture_size=0;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &Max_texture_size);
  std::cerr << "Max texture size: " << Max_texture_size << "\n";

  glClearColor(1.0,1.0,1.0,1.0);
  glEnable(GL_DEPTH_TEST);;

  Observer_angle_x=0;
  Observer_angle_y=0;
  Observer_distance=DEFAULT_DISTANCE;
}

