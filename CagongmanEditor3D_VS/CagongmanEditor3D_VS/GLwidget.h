#pragma once

#include <QObject>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtGui/QOpenGLFunctions>

class GLwidget  : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

protected:
	void initializeGL() override;
	void paintGL() override;

public:
	explicit GLwidget(QWidget *parent);
	~GLwidget();
};
