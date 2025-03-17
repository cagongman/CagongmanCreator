#ifndef CMEDITOR_H
#define CMEDITOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class CMEditor;
}
QT_END_NAMESPACE

class CMEditor : public QMainWindow
{
    Q_OBJECT

public:
    CMEditor(QWidget *parent = nullptr);
    ~CMEditor();

private:
    Ui::CMEditor *ui;
};
#endif // CMEDITOR_H
