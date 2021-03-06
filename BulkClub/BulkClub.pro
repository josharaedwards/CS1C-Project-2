QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addinvpopup.cpp \
    addmemberpopup.cpp \
    addsalepopup.cpp \
    authenticate.cpp \
    dbmanager.cpp \
    deletememberpopup.cpp \
    helperLib.cpp \
    main.cpp \
    mainwindow.cpp \
    member.cpp \
    memberpopup.cpp \
    inventory.cpp \
    membertypepopup.cpp \
    sale.cpp \
    salespopup.cpp \
    splashscreen.cpp

HEADERS += \
    addinvpopup.h \
    addmemberpopup.h \
    addsalepopup.h \
    authenticate.h \
    dbmanager.h \
    deletememberpopup.h \
    helperLib.h \
    mainwindow.h \
    member.h \
    memberpopup.h \
    inventory.h \
    membertypepopup.h \
    sale.h \
    salespopup.h \
    splashscreen.h

FORMS += \
    addinvpopup.ui \
    addmemberpopup.ui \
    addsalepopup.ui \
    deletememberpopup.ui \
    mainwindow.ui \
    memberpopup.ui \
    membertypepopup.ui \
    salespopup.ui \
    splashscreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    bulk-club.sqlite
