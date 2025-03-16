#pragma once

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>

class GLWidget  : public QOpenGLWidget
{
	Q_OBJECT

public:
	GLWidget(QObject *parent);
	~GLWidget();
};
