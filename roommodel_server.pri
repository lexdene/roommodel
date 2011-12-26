INCLUDEPATH += $$PWD/include/server $$PWD/include/common
LIBS += -L../../roommodel/server/ -lserver
unix:!mac:QMAKE_LFLAGS += -Wl,--rpath=../../roommodel/server
