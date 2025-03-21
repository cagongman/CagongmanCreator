#include "GLwidget.h"

GLwidget::GLwidget(QWidget* parent) : QOpenGLWidget(parent) 
{

}

void GLwidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
}

void GLwidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLwidget::~GLwidget()
{}
