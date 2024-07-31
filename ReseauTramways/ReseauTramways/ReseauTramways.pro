QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Coordonnees.cpp \
    Simulationtram.cpp \
    arretstrams.cpp \
    lignestrams.cpp \
    main.cpp \
    tramways.cpp

HEADERS += \
    ArretsTrams.h \
    Coordonnees.h \
    LignesTrams.h \
    Simulationtram.h \
    Tramways.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ReseauTramways.pro.user

QT += core gui xml
