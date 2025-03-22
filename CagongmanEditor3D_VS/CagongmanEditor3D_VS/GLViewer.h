#pragma once

#include <QObject>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtGui/QOpenGLFunctions>

class GLViewer  : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

protected:
	void initializeGL() override;
	void paintGL() override;

public:
	explicit GLViewer(QWidget *parent);
	~GLViewer();
};
