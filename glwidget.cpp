#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QWidget(parent) {
    auto *view = new Qt3DExtras::Qt3DWindow();
    auto *rootEntity = new Qt3DCore::QEntity();

    // 3D 모델 로드
    auto *mesh = new Qt3DRender::QMesh(rootEntity);
    mesh->setSource(QUrl::fromLocalFile("assets/models/sample.ply"));

    // 카메라 설정
    auto *camera = view->camera();
    // camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    // camera->setPosition(QVector3D(0, 0, 10));
    // camera->setViewCenter(QVector3D(0, 0, 0));

    auto *cameraController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    cameraController->setCamera(camera);

    view->setRootEntity(rootEntity);
    view->show();
}
