#include "CMeditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CMEditor window;
    window.show();
    return app.exec();
}
