CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(weathermoduleplugin)
TEMPLATE    = lib

HEADERS     = weathermoduleplugin.h
SOURCES     = weathermoduleplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

QT += designer

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(weathermodule.pri)
