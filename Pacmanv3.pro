QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gameItems/ghost.cpp \
    gameItems/pacman.cpp \
    gameItems/sprite.cpp \
    gameItems/tile.cpp \
    gameItems/visual.cpp \
    gameLogic/controlleraggressive.cpp \
    gameLogic/controllerpredictive.cpp \
    gameLogic/controllerpursuit.cpp \
    gameLogic/controllerrandom.cpp \
    gameLogic/game.cpp \
    gameLogic/ghostcontroller.cpp \
    gameLogic/level.cpp \
    main.cpp \
    util/direction.cpp \
    util/idx.cpp \
    util/vec.cpp \
    windows/leveleditor.cpp \
    windows/levelmaker.cpp \
    windows/mainwindow.cpp

HEADERS += \
    gameItems/ghost.h \
    gameItems/pacman.h \
    gameItems/sprite.h \
    gameItems/tile.h \
    gameItems/visual.h \
    gameLogic/controlleraggressive.h \
    gameLogic/controllerpredictive.h \
    gameLogic/controllerpursuit.h \
    gameLogic/controllerrandom.h \
    gameLogic/game.h \
    gameLogic/ghostcontroller.h \
    gameLogic/level.h \
    util/constants.h \
    util/direction.h \
    util/idx.h \
    util/vec.h \
    windows/leveleditor.h \
    windows/levelmaker.h \
    windows/mainwindow.h

FORMS += \
    levelmaker.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
