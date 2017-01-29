QT += qml quick

HEADERS += squircle.h \
    jsmn.h
SOURCES += squircle.cpp main.cpp \
    jsmn.c
RESOURCES += ckeys.qrc

target.path = bin
INSTALLS += target

DISTFILES += \
    ../data/Button.qml \
    ../data/main.qml
