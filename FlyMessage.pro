#-------------------------------------------------
#
# Project created by QtCreator 2019-09-20T17:23:17
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlyMessage
TEMPLATE = app
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        FlyMessage.cpp \
    fm_sidebar.cpp \
    webwizardform.cpp \
    fm_setting.cpp \
    fm_notice.cpp \
    fm_json.cpp \
    fm_floatwindow.cpp \
    fm_mainwindow.cpp \
    fm_mainwindowproxy.cpp \
    fm_news.cpp \
    fm_settingform.cpp \
    fm_titlebar.cpp \
    fm_waitwidget.cpp \
    fm_connectform.cpp


HEADERS += \
        FlyMessage.h \
    fm_sidebar.h \
    webwizardform.h \
    fm_setting.h \
    aero.h \
    fm_notice.h \
    fm_json.h \
    fm_floatwindow.h \
    fm_mainwindow.h \
    fm_mainwindowproxy.h \
    fm_news.h \
    fm_settingform.h \
    fm_titlebar.h \
    fm_waitwidget.h \
    fm_connectform.h

RC_FILE += FlyMessage.rc

RESOURCES += \
    resource.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    settingform.ui \
    webwizardform.ui \
    connectform.ui

