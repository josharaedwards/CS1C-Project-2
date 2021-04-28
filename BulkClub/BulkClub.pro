QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authenticate.cpp \
    dbmanager.cpp \
    helperLib.cpp \
    inventory.cpp \
    main.cpp \
    mainwindow.cpp \
    member.cpp \
    memberpopup.cpp \
    sale.cpp

HEADERS += \
    authenticate.h \
    dbmanager.h \
    helperLib.h \
    inventory.h \
    mainwindow.h \
    member.h \
    memberpopup.h \
    sale.cpp \

FORMS += \
    mainwindow.ui \
    memberpopup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    bulk-club.sqlite
