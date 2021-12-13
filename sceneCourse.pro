#-------------------------------------------------
#
# Project created by QtCreator 2019-10-02T17:53:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sceneCourse
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
    scene.cpp \
    size.cpp \
    point.cpp \
    figure.cpp \
    rectangle.cpp \
    cylinder.cpp \
    angle.cpp \
    tree.cpp \
    logic/road.cpp \
    logic/roadline.cpp \
    logic/world.cpp \
    logic/worldobject.cpp \
    controller/controller.cpp \
    logic/treeLogic.cpp \
    logic/carLogic.cpp \
    triangle.cpp \
    carScene.cpp \
    logic/roadmark.cpp \
    camera.cpp \
    objfigure.cpp \
    zbuffer.cpp \
    logic/sunlogic.cpp \
    logic/ground.cpp

HEADERS += \
        mainwindow.h \
    scene.h \
    size.h \
    point.h \
    figure.h \
    rectangle.h \
    cylinder.h \
    angle.h \
    tree.h \
    logic/road.h \
    logic/roadline.h \
    logic/world.h \
    logic/worldobject.h \
    controller/controller.h \
    logic/treeLogic.h \
    logic/infoobject.h \
    logic/carLogic.h \
    triangle.h \
    carScene.h \
    logic/roadmark.h \
    camera.h \
    objfigure.h \
    zbuffer.h \
    defines.h \
    logic/sunlogic.h \
    logic/ground.h

FORMS += \
        mainwindow.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
