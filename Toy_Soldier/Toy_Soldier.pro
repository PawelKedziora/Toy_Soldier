QT       += core gui widgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    Bullet.cpp \
    Enemy.cpp \
    Game.cpp \
    Health.cpp \
    Player.cpp \
    PlayerOfficer.cpp \
    Score.cpp \
    main.cpp \
    uiform.cpp

HEADERS += \
    Bullet.h \
    Enemy.h \
    Game.h \
    Health.h \
    Player.h \
    PlayerOfficer.h \
    Score.h \
    uiform.h

FORMS += \
    UiForm.ui

RESOURCES += \
    res.qrc
