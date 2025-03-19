#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/QOrbitCameraController>

class GLWidget : public QWidget {
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = nullptr);
};

#endif // GLWIDGET_H