include(../../Dlut-Game-Platform/api/api.pri)
include(../common/common.pri)
QT       += network
QT       -= gui

TARGET = server
TEMPLATE = lib

SOURCES += \
	network/jroommodelserver.cpp \
    network/jroommodelserverroomprocessor.cpp \
    network/jroommodelservergamedataprocessor.cpp \
    manager/jroommanager.cpp \
    application/jserverapplicationbase.cpp \
    manager/japplicationmanager.cpp \
    application/jserverapplicationfactorybase.cpp

HEADERS += \
	network/jroommodelserver.h \
    network/jroommodelserverroomprocessor.h \
    network/jroommodelservergamedataprocessor.h \
    manager/jroommanager.h \
    application/jserverapplicationbase.h \
    manager/japplicationmanager.h \
    application/jserverapplicationfactorybase.h