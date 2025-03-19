#include "CMeditor.h"
#include "ui_CMeditor.h"

CMEditor::CMEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CMEditor)
{
    ui->setupUi(this);
}

CMEditor::~CMEditor()
{
    delete ui;
}
