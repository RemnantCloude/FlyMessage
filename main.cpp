#include <QApplication>

#include "FlyMessage.h"
#include "fm_sidebar.h"
#include "settingform.h"
#include "webwizardform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WebWizardForm w;
    w.show();
    return a.exec();
}
