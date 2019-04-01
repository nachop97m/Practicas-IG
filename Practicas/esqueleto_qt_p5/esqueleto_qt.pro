HEADERS += \
  glwidget.h \
  window.h \
    o3ds.h \
    o3d.h \
    cubo.h \
    tetraedro.h \
    o3dply.h \
    file_ply_stl.h \
    o3drevolucion.h \
    cilindro.h \
    vaso.h \
    vaso_inv.h \
    cono.h \
    tubo.h \
    peon.h \
    esfera.h \
    brazo.h \
    basesup.h \
    basemed.h \
    baseinf.h \
    ejerotacion.h \
    extremidad.h \
    extremidad2.h \
    tablero.h

SOURCES += \
  main.cc \
  glwidget.cc \
  window.cc \
    o3ds.cpp \
    o3d.cpp \
    cubo.cpp \
    tetraedro.cpp \
    o3dply.cpp \
    file_ply_stl.cc \
    o3drevolucion.cpp \
    cilindro.cpp \
    vaso.cpp \
    vaso_inv.cpp \
    cono.cpp \
    tubo.cpp \
    peon.cpp \
    esfera.cpp \
    brazo.cpp \
    basesup.cpp \
    basemed.cpp \
    baseinf.cpp \
    ejerotacion.cpp \
    extremidad.cpp \
    extremidad2.cpp \
    tablero.cpp

INCLUDEPATH += /usr/include/GL

LIBS += -L/usr/lib64 -lGL \
        -lGLEW \
        -L/casa/dmartin/codigo/funciontecas/glew/lib -lGLEW

CONFIG += c++11
QT += widgets
