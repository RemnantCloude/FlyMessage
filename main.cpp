#include <QApplication>

#include "FlyMessage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FlyMessage w;
    w.show();

    return a.exec();
}
