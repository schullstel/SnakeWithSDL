TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
QT += core

SOURCES += \
        Drawer.cpp \
        Elmo.cpp \
        Food.cpp \
        GameBoard.cpp \
        Tools/RandomNumberGenerator.cpp \
        main.cpp

win32: LIBS += -L$$PWD/../../../SDL2-2.0.22/x86_64-w64-mingw32/lib/ -lSDL2

INCLUDEPATH += $$PWD/../../../SDL2-2.0.22/x86_64-w64-mingw32/include/SDL2
DEPENDPATH += $$PWD/../../../SDL2-2.0.22/x86_64-w64-mingw32/include/SDL2

HEADERS += \
    Drawer.hpp \
    Elmo.hpp \
    Food.hpp \
    GameBoard.hpp \
    Tools/RandomNumberGenerator.hpp

win32: LIBS += -L$$PWD/../../../SDL2_image-2.0.5/x86_64-w64-mingw32/lib/ -lSDL2_image

INCLUDEPATH += $$PWD/../../../SDL2_image-2.0.5/x86_64-w64-mingw32/include/SDL2
DEPENDPATH += $$PWD/../../../SDL2_image-2.0.5/x86_64-w64-mingw32/include/SDL2
