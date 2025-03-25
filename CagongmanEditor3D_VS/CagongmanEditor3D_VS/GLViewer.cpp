#include "GLViewer.h"
#include <QFile>
#include <QTExtStream>
#include <QDebug>

GLViewer::GLViewer(QWidget* parent) : QOpenGLWidget(parent) 
{
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
}

void GLViewer::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    bool ok =
        m_shader.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/BasicShader.vert") &&
        m_shader.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/BasicShader.frag") &&
        m_shader.link();

    if (!ok) {
        qDebug() << "Shader compile/link failed:";
        qDebug() << m_shader.log();
    }

    // VAO & VBO »ý¼º
    m_vao.create();
    m_vao.bind();

    m_vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vbo.create();
    m_vbo.bind();
    m_vbo.setUsagePattern(QOpenGLBuffer::DynamicDraw);

    m_shader.enableAttributeArray(0);
    m_shader.setAttributeBuffer(0, GL_FLOAT, 0, 3);

    m_vao.release();
    m_vbo.release();
}

void GLViewer::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_vertices.empty()) return;

    QMatrix4x4 proj;
    float aspect = float(width()) / float(height());
    proj.ortho(-aspect * m_zoom, aspect * m_zoom,   // left, right
        -m_zoom, m_zoom,                     // bottom, top
        0.1f, 100.0f);                       // near, far

    QMatrix4x4 view;
    view.lookAt(QVector3D(0, 0, 3), QVector3D(0, 0, 0), QVector3D(0, 1, 0));

    QMatrix4x4 model;
    model.rotate(m_rotationX, 1, 0, 0);
    model.rotate(m_rotationY, 0, 1, 0);

    QMatrix4x4 mvp = proj * view * model;

    m_shader.bind();
    m_shader.setUniformValue("mvp", mvp);
    m_vao.bind();

    m_vbo.bind();
    m_vbo.allocate(m_vertices.data(), m_vertices.size() * sizeof(float));

    glDrawArrays(GL_POINTS, 0, m_vertices.size() / 3);

    m_vbo.release();
    m_vao.release();
    m_shader.release();
}

bool GLViewer::LoadMesh(const QString &filePath) {
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "File open failed: " << filePath;
        return false;
    }

    m_vertices.clear();
    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.startsWith("v ")) {
            QStringList parts = line.split(" ", Qt::SkipEmptyParts);
            if (parts.size() == 4) {
                m_vertices.push_back(parts[1].toFloat());
                m_vertices.push_back(parts[2].toFloat());
                m_vertices.push_back(parts[3].toFloat());
            }
        }
    }

    file.close();
    update();
    return true;
}

void GLViewer::wheelEvent(QWheelEvent* event) {
    if (event->angleDelta().y() > 0) {
        m_zoom *= 1.1f;
    }
    else {
        m_zoom /= 1.1f;
    }
    
    update();
}

void GLViewer::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        m_lastMousePos = event->pos();
    }
}

void GLViewer::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        QPoint delta = event->pos() - m_lastMousePos;
        m_lastMousePos = event->pos();

        m_rotationX += delta.y();
        m_rotationY += delta.x();

        update();
    }
}

GLViewer::~GLViewer() {

}
