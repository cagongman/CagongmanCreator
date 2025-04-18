#include "Viewer.h"
#include <QFile>
#include <QTExtStream>
#include <QDebug>

Viewer::Viewer(QWidget* parent) : QOpenGLWidget(parent) 
{
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
}

void Viewer::initializeGL() {
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

    // VAO & VBO 생성
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

void Viewer::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_objects.empty()) return;

    float viewSize = 1.0f;  // 줌 크기 조절용 값
    float aspect = float(width()) / float(height());

    m_projMat.ortho(-aspect * viewSize, aspect * viewSize,
        -viewSize, viewSize,
        0.1f, 100.0f);

    float radYaw = qDegreesToRadians(m_yaw);
    float radPitch = qDegreesToRadians(m_pitch);

    QVector3D target(0, 0, 0);
    QVector3D eye(
        m_distance * cos(radPitch) * sin(radYaw),
        m_distance * sin(radPitch),
        m_distance * cos(radPitch) * cos(radYaw)
    );
    QVector3D up(0, 1, 0);

    m_viewMat.lookAt(eye, target, up);

    QMatrix4x4 mvp = m_projMat * m_viewMat * m_modelMat;

    m_shader.bind();
    m_shader.setUniformValue("mvp", mvp);

    for (const auto& obj : m_objects) {
        if (obj->getVertexCount() == 0)
            continue;

        m_vbo.bind();
        m_vbo.allocate(obj->getVertexBuffer(), obj->getVertexCount() * 3 * sizeof(float));

        glDrawArrays(GL_POINTS, 0, obj->getVertexCount());
    }

    m_vbo.release();
    m_shader.release();
}

bool Viewer::loadMesh(const QString &filePath) {
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "File open failed: " << filePath;
        return false;
    }

    Object* obj = new Object();
    std::vector<float> vertices;
    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.startsWith("v ")) {
            QStringList parts = line.split(" ", Qt::SkipEmptyParts);
            if (parts.size() == 4) {
                vertices.push_back(parts[1].toFloat());
                vertices.push_back(parts[2].toFloat());
                vertices.push_back(parts[3].toFloat());
            }
        }
    }

    obj->setVertices(std::move(vertices));
    m_objects.push_back(obj);

    file.close();
    update();
    return true;
}

void Viewer::wheelEvent(QWheelEvent* event) {
    if (event->angleDelta().y() > 0) {
        m_zoom *= 1.1f;
    }
    else {
        m_zoom /= 1.1f;
    }
    
    update();
}

void Viewer::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        m_lastMousePos = event->pos();
    }
}

void Viewer::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        QPoint delta = event->pos() - m_lastMousePos;
        m_lastMousePos = event->pos();

        m_yaw += delta.x() * 0.5f;
        m_pitch += delta.y() * 0.5f;

        m_pitch = std::clamp(m_pitch, -89.0f, 89.0f);

        update();
    }
}

Viewer::~Viewer() {

}
