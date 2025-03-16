#include "MainWindow.h"
#include "GLWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindowClass()),
    glWidget(new GLWidget(this))
{
    ui->setupUi(this);

    setWindowTitle("3D Viewer");
    setCentralWidget(glWidget);
    resize(800, 600);
}

MainWindow::~MainWindow()
{}
