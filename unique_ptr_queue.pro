TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        test_unique_ptr_queue.cpp

INCLUDEPATH += /usr/src/gtest/include/gtest \
            /usr/src/gmock/include/gmock

LIBS += -L/usr/local/lib/
LIBS += -lgtest -L/usr/local/lib/googletest -lpthread

HEADERS += \
    blockingqueue.h

DISTFILES += \
    LICENSE.txt \
    README.md
