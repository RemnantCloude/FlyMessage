#include <QApplication>

#include "FlyMessage.h"
#include "waitwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FlyMessage w;
    w.show();
    w.setBackgroundImage();
    return a.exec();
}
