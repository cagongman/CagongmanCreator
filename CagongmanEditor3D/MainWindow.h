#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class GLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindowClass* ui;
    GLWidget* glWidget;
};
