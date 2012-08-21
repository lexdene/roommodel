TEMPLATE = lib
include(../dgpapi.pri)
include(../common/common.pri)

HEADERS += \
    network/jroommodelclientroomprocessor.h \
    network/jroommodelclientgamedataprocessor.h \
    network/jroommodelclientsocket.h \
    application/jclientapplicationbase.h \
    gui/jroomwidget.h \
    gui/jroomlistmodel.h \
    service/jroommodelclientstartup.h

SOURCES += \
    network/jroommodelclientroomprocessor.cpp \
    network/jroommodelclientgamedataprocessor.cpp \
    network/jroommodelclientsocket.cpp \
    application/jclientapplicationbase.cpp \
    gui/jroomwidget.cpp \
    gui/jroomlistmodel.cpp \
    service/jroommodelclientstartup.cpp

FORMS += \
    gui/jroomwidget.ui
