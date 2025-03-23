#include "GLViewer.h"
#include <QFile>
#include <QTExtStream>
#include <QDebug>

GLViewer::GLViewer(QWidget* parent) : QOpenGLWidget(parent) 
{

}

void GLViewer::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    // 嘉捞歹 积己
    m_shader.addShaderFromSourceCode(QOpenGLShader::Vertex,
        "#version 330 core\n"
        "layout(location = 0) in vec3 position;\n"
        "void main() {\n"
        "   gl_Position = vec4(position, 1.0);\n"
        "}"
    );
    m_shader.addShaderFromSourceCode(QOpenGLShader::Fragment,
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "   FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
        "}"
    );
    m_shader.link();

    // VAO & VBO 积己
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

    m_shader.bind();
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

GLViewer::~GLViewer()
{}
