QT       += core gui
QT += widgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    alarma.cpp \
    crearalarma.cpp \
    cronometro.cpp \
    main.cpp \
    ventanaalarma.cpp \
    widget.cpp

HEADERS += \
    alarma.h \
    crearalarma.h \
    cronometro.h \
    ventanaalarma.h \
    widget.h

FORMS += \
    crearalarma.ui \
    cronometro.ui \
    ventanaalarma.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc
