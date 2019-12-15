#include <QApplication>

#include "FlyMessage.h"
#include "webwizardform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FM_Setting f;
    FlyMessage w;
    w.show();
    return a.exec();
}
