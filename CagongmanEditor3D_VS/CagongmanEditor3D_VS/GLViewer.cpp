#include "GLViewer.h"

GLViewer::GLViewer(QWidget* parent) : QOpenGLWidget(parent) 
{

}

void GLViewer::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
}

void GLViewer::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLViewer::~GLViewer()
{}
