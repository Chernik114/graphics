#-------------------------------------------------
#
# Project created by QtCreator 2019-02-07T11:23:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = life
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
        mainwindow.cpp \
    drawwidget.cpp \
    pixdrawer.cpp \
    regpolygon.cpp \
    hexagons.cpp \
    tableview.cpp \
    animator.cpp \
    igameview.cpp \
    gameview.cpp \
    mousegameview.cpp \
    filewatcher.cpp \
    settingsdialog.cpp \
    scrolledit.cpp \
    filedriver.cpp \
    qgameview.cpp \
    settingsdriver.cpp \
    about.cpp

HEADERS += \
        mainwindow.h \
    drawwidget.h \
    pixdrawer.h \
    regpolygon.h \
    hexagons.h \
    tableview.h \
    animator.h \
    igameview.h \
    gameview.h \
    mousegameview.h \
    filewatcher.h \
    settingsdialog.h \
    scrolledit.h \
    filedriver.h \
    qgameview.h \
    settingsdriver.h \
    about.h

FORMS += \
        mainwindow.ui \
    settingsdialog.ui \
    about.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
