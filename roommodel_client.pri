INCLUDEPATH += $$PWD/include/client $$PWD/include/common
LIBS += -L../../roommodel/client/ -lclient
unix:!mac:QMAKE_LFLAGS += -Wl,--rpath=../../roommodel/client
