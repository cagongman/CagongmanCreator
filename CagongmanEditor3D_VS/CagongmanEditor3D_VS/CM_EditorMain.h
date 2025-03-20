#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CM_EditorMain.h"

class CM_EditorMain : public QMainWindow
{
    Q_OBJECT

public:
    CM_EditorMain(QWidget *parent = nullptr);
    ~CM_EditorMain();

private:
    Ui::CM_EditorMainClass ui;
};
