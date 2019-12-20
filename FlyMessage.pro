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
        main_window.cpp \
        title_bar.cpp \
    news.cpp \
    fm_sidebar.cpp \
    settingform.cpp \
    float_window.cpp \
    webwizardform.cpp \
    fm_setting.cpp \
    fm_notice.cpp \
    mainwindowproxy.cpp \
    waitwidget.cpp \
    fm_json.cpp


HEADERS += \
        FlyMessage.h \
        main_window.h \
        title_bar.h \
    news.h \
    fm_sidebar.h \
    settingform.h \
    float_window.h \
    webwizardform.h \
    fm_setting.h \
    aero.h \
    fm_notice.h \
    mainwindowproxy.h \
    waitwidget.h \
    fm_json.h

RC_FILE += FlyMessage.rc

RESOURCES += \
    resource.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    settingform.ui \
    webwizardform.ui

