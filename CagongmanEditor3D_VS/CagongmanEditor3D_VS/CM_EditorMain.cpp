#include "CM_EditorMain.h"
#include <QVBoxLayout>

CM_EditorMain::CM_EditorMain(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CM_EditorMainClass)
{
    ui->setupUi(this);

    setWindowTitle("3D Viewer");
    resize(1024, 768);

    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    viewer = new Viewer(this);
    layout->addWidget(viewer);

    QToolBar* toolBar = addToolBar("Toolbar");
    QAction* openAction = toolBar->addAction("Open");
    QAction* infoAction = toolBar->addAction("Info");

    connect(openAction, &QAction::triggered, this, &CM_EditorMain::openFile);
    connect(infoAction, &QAction::triggered, this, &CM_EditorMain::showInfo);
}

void CM_EditorMain::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open 3D Model", "", "OBJ Files (*.obj);;All Files (*)");
    if (!fileName.isEmpty()) {
        // QMessageBox::information(this, "File Opened", "Loaded: " + fileName);
        if (!viewer->loadMesh(fileName)) {
            QMessageBox::warning(this, "Error", "Failed to load the file.");
        }
    }
}

void CM_EditorMain::showInfo() {
    QMessageBox::information(this, "About", "3D Viewer - Created with Qt and OpenGL");
}


CM_EditorMain::~CM_EditorMain()
{
    delete ui;
}