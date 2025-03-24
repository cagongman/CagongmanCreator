#pragma once

#include <QObject>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtGui/QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QWheelEvent>
#include <QMatrix4x4>

class GLViewer  : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

protected:
	void initializeGL() override;
	void paintGL() override;
	void wheelEvent(QWheelEvent* event) override;

	std::vector<float> m_vertices;
	QOpenGLVertexArrayObject m_vao;
	QOpenGLBuffer m_vbo;
	QOpenGLShaderProgram m_shader;

	float m_zoom = 1.0f;

public:
	explicit GLViewer(QWidget *parent);
	bool LoadMesh(const QString& filePath);

	~GLViewer();
};
