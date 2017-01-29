QT += qml quick

HEADERS += squircle.h \
    jsmn.h \
    keyboard.h \
    comboboxmodel.h
SOURCES += squircle.cpp main.cpp \
    jsmn.c \
    keyboard.cpp \
    comboboxmodel.cpp
RESOURCES += ckeys.qrc

target.path = bin
INSTALLS += target

DISTFILES += \
    ../data/Button.qml \
    ../data/main.qml
