#include <QApplication>

#include "FlyMessage.h"
#include "fm_sidebar.h"
#include "settingform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FlyMessage w;
    w.show();
    return a.exec();
}
