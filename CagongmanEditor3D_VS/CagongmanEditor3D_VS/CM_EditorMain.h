#pragma once

#include <QtWidgets/QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include "Viewer.h"
#include "ui_CM_EditorMain.h"

class CM_EditorMain : public QMainWindow
{
    Q_OBJECT

public:
    CM_EditorMain(QWidget *parent = nullptr);
    ~CM_EditorMain();

private:
    Ui::CM_EditorMainClass *ui;
    Viewer* viewer;

private slots:
    void openFile();
    void showInfo();
};
