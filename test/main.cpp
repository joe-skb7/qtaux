#include <QtGui/QApplication>
#include "test.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Test t;
    t.exec();

    return app.exec();
}
