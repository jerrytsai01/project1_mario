QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    boxbricks.cpp \
    brokenbricks.cpp \
    bullet.cpp \
    fireflower.cpp \
    floorbricks.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    mario.cpp \
    normalbricks.cpp \
    stonebricks.cpp \
    supermushroom.cpp \
    toxicmushroom.cpp \
    waterpipe.cpp \
    coin.cpp

HEADERS += \
    boxbricks.h \
    brokenbricks.h \
    bullet.h \
    fireflower.h \
    floorbricks.h \
    loginwindow.h \
    mainwindow.h \
    mario.h \
    normalbricks.h \
    stonebricks.h \
    supermushroom.h \
    toxicmushroom.h \
    waterpipe.h \
    coin.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    Mario_zh_TW.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    data.qrc
