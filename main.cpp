#include <QApplication>
#include <QSplashScreen>
#include <QtNetwork>
#include <QMessageBox>
#include "FlyMessage.h"
#include "waitwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
        
    QPixmap pixmap(":/images/splash");
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();
    
    QHostInfo info = QHostInfo::fromName(QString("www.baidu.com"));
    if(info.addresses().isEmpty())
    {
        QMessageBox::critical(nullptr, "飞讯", "未检测到有效的网络连接\n\n"
                                             "请检查网络后重新运行程序。","朕知道了");
        return -1;
    }
    
    FlyMessage w;
    w.show();
    w.setBackgroundImage();
    
    splash.finish(&w);
    
    return a.exec();
}
