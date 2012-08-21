TEMPLATE = lib
include(../dgpapi.pri)
include(../common/common.pri)
QT       += network
QT       -= gui

TARGET = server

SOURCES += \
	network/jroommodelserver.cpp \
    network/jroommodelserverroomprocessor.cpp \
    network/jroommodelservergamedataprocessor.cpp \
    network/jroommodelserverdisconnectedprocessor.cpp \
    manager/jroommanager.cpp \
    application/jserverapplicationbase.cpp \
    manager/japplicationmanager.cpp \
    application/jserverapplicationfactorybase.cpp

HEADERS += \
	network/jroommodelserver.h \
    network/jroommodelserverroomprocessor.h \
    network/jroommodelservergamedataprocessor.h \
    network/jroommodelserverdisconnectedprocessor.h \
    manager/jroommanager.h \
    application/jserverapplicationbase.h \
    manager/japplicationmanager.h \
    application/jserverapplicationfactorybase.h
