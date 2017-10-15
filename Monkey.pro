#-------------------------------------------------
#
# Project created by QtCreator 2017-10-05T13:23:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Monkey
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        mainwindow.cpp \
    settings.cpp \
    rules.cpp \
    sequence.cpp \
    stream.cpp \
    handler.cpp

HEADERS  += mainwindow.h \
    settings.h \
    rules.h \
    sequence.h \
    stream.h \
    handler.h

FORMS    += mainwindow.ui

INCLUDEPATH += C:\code\opencv\build\include

LIBS += C:\code\opencv-build\bin\libopencv_core330.dll
LIBS += C:\code\opencv-build\bin\libopencv_highgui330.dll
LIBS += C:\code\opencv-build\bin\libopencv_imgcodecs330.dll
LIBS += C:\code\opencv-build\bin\libopencv_imgproc330.dll
LIBS += C:\code\opencv-build\bin\libopencv_features2d330.dll
LIBS += C:\code\opencv-build\bin\libopencv_calib3d330.dll
