QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += ./ui
SOURCES += \
    function/weatherdata.cpp \
    ui/bilibili.cpp \
    ui/car.cpp \
    ui/ctrlcenter.cpp \
    ui/gaodemap.cpp \
    ui/main.cpp \
    ui/qqmusic.cpp \
    ui/voiceasst.cpp \
    ui/weather.cpp \
    ui/widget.cpp

HEADERS += \
    function/weatherdata.h \
    ui/bilibili.h \
    ui/car.h \
    ui/ctrlcenter.h \
    ui/gaodemap.h \
    ui/qqmusic.h \
    ui/voiceasst.h \
    ui/weather.h \
    ui/widget.h

FORMS += \
    ui/bilibili.ui \
    ui/car.ui \
    ui/ctrlcenter.ui \
    ui/gaodemap.ui \
    ui/qqmusic.ui \
    ui/voiceasst.ui \
    ui/weather.ui \
    ui/widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
