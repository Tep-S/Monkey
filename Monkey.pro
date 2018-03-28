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
    mouse/RunMouse.cpp \
    lua/luapusher.cpp \
    roadmap.cpp

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
    lua/lua/include/lauxlib.h \
    lua/lua/include/lua.h \
    lua/lua/include/lua.hpp \
    lua/lua/include/luaconf.h \
    lua/lua/include/lualib.h \
    lua/luabridge/detail/CFunctions.h \
    lua/luabridge/detail/ClassInfo.h \
    lua/luabridge/detail/Constructor.h \
    lua/luabridge/detail/dump.h \
    lua/luabridge/detail/FuncTraits.h \
    lua/luabridge/detail/Iterator.h \
    lua/luabridge/detail/LuaException.h \
    lua/luabridge/detail/LuaHelpers.h \
    lua/luabridge/detail/LuaRef.h \
    lua/luabridge/detail/Namespace.h \
    lua/luabridge/detail/Stack.h \
    lua/luabridge/detail/TypeList.h \
    lua/luabridge/detail/TypeTraits.h \
    lua/luabridge/detail/Userdata.h \
    lua/luabridge/LuaBridge.h \
    lua/luabridge/RefCountedObject.h \
    lua/luabridge/RefCountedPtr.h \
    lua/luapusher.h \
    linefinder.h \
    roadmap.h
FORMS    += mainwindow.ui

#INCLUDEPATH += C:\code\opencv\build\include
INCLUDEPATH += C:\Users\Sam\Desktop\code\opencv\build\include
INCLUDEPATH += C:\Users\Sam\Desktop\code\opencv\opencv_contrib331\modules\xfeatures2d\include
MYPATH = C:\Users\Sam\Desktop\code\opencv-build\bin

LIBS += $${MYPATH}\libopencv_flann331.dll
LIBS += $${MYPATH}\libopencv_xfeatures2d331.dll
LIBS += $${MYPATH}\libopencv_features2d331.dll
LIBS += $${MYPATH}\libopencv_highgui331.dll
LIBS += $${MYPATH}\libopencv_imgcodecs331.dll
LIBS += $${MYPATH}\libopencv_imgproc331.dll
LIBS += $${MYPATH}\libopencv_calib3d331.dll
LIBS += $${MYPATH}\libopencv_core331.dll

INCLUDEPATH += $$PWD/lua/lua/include
DEPENDPATH += $$PWD/lua/lua/include


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lua/lua/ -llua53
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lua/lua/ -llua53d

