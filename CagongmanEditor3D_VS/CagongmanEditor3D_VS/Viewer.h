#pragma once

#include <QObject>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtGui/QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QMatrix4x4>
#include "Object.h"

class Viewer  : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

protected:
	void initializeGL() override;
	void paintGL() override;
	void wheelEvent(QWheelEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

	std::vector<Object*> m_objects;

	QMatrix4x4 m_modelMat;
	QMatrix4x4 m_viewMat;
	QMatrix4x4 m_projMat;

	std::vector<float> m_vertices;

	QOpenGLVertexArrayObject m_vao;
	QOpenGLBuffer m_vbo;
	QOpenGLShaderProgram m_shader;

	QPoint m_lastMousePos;

	float m_pitch = 0.0f;
	float m_yaw = 0.0f;
	float m_distance = 100.0f;

	float m_zoom = 1.0f;
	float m_rotationX = 0.0f;
	float m_rotationY = 0.0f;

public:
	explicit Viewer(QWidget *parent);
	bool loadMesh(const QString& filePath);

	~Viewer();
};
