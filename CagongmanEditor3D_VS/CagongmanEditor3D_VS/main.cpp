#include "CM_EditorMain.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CM_EditorMain w;
    w.show();
    return a.exec();
}
