#include "CMeditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CMEditor w;
    w.show();
    return a.exec();
}
