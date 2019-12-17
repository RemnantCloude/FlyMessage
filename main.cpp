#include <QApplication>
#include <QSplashScreen>
#include "FlyMessage.h"
#include "waitwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/images/splash");
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();
    FlyMessage w;
    
    w.show();
    w.setBackgroundImage();
    splash.finish(&w);
    return a.exec();
}
