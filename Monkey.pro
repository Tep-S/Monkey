#-------------------------------------------------
#
# Project created by QtCreator 2017-10-05T13:23:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Monkey
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        mainwindow.cpp \
    settings.cpp \
    rules.cpp \
    sequence.cpp \
    stream.cpp \
    handler.cpp \
    qcustomplot.cpp \
    mouse/BezierCurve.cpp \
    mouse/Normal.cpp \
    mouse/RunMouse.cpp

HEADERS  += mainwindow.h \
    settings.h \
    rules.h \
    sequence.h \
    stream.h \
    handler.h \
    qcustomplot.h \
    ui_mainwindow.h \
    mouse/BezierCurve.h \
    mouse/Normal.h \
    mouse/RunMouse.h \
    lua/lua/include/lauxlib.h \
    lua/lua/include/lua.h \
    lua/lua/include/lua.hpp \
    lua/lua/include/luaconf.h \
    lua/lua/include/lualib.h \

FORMS    += mainwindow.ui

#INCLUDEPATH += C:\code\opencv\build\include
INCLUDEPATH += C:\Users\Sam\Desktop\code\opencv\build\include
MYPATH = C:\Users\Sam\Desktop\code\opencv-build\bin

#LIBS += $${MYPATH}\libopencv_core330.dll
#LIBS += $${MYPATH}\libopencv_highgui330.dll
#LIBS += $${MYPATH}\libopencv_imgcodecs330.dll
#LIBS += $${MYPATH}\libopencv_imgproc330.dll
#LIBS += $${MYPATH}\libopencv_features2d330.dll
#LIBS += $${MYPATH}\libopencv_calib3d330.dll

LIBS += $${MYPATH}\libopencv_core331.dll
LIBS += $${MYPATH}\libopencv_highgui331.dll
LIBS += $${MYPATH}\libopencv_imgcodecs331.dll
LIBS += $${MYPATH}\libopencv_imgproc331.dll
LIBS += $${MYPATH}\libopencv_features2d331.dll
LIBS += $${MYPATH}\libopencv_calib3d331.dll

#LIBS += \
#    lua/lua/liblua53.a \
#    lua/lua/lua53.dll

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lua/lua/ -llua53
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lua/lua/ -llua53d

INCLUDEPATH += $$PWD/lua/lua/include
DEPENDPATH += $$PWD/lua/lua/include
