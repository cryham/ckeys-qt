QT += qml quick

HEADERS += \
    jsmn.h \
    keyboard.h \
    ComboBoxModel.h
    background.h
SOURCES += main.cpp \
    jsmn.c \
    keyboard.cpp \
    ComboBoxModel.cpp
    background.cpp
RESOURCES +=

target.path = bin
INSTALLS += target

DISTFILES += \
    ../data/Button.qml \
    ../data/main.qml
