TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++17
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ./includes

LIBS += -L$$_PRO_FILE_PWD_/libs

LIBS += -lmazify -lcurses-helper-utils
LIBS += -lpdcurses

SOURCES += \
        game-map-utils.cpp \
        main.cpp \
        random-utils.cpp

HEADERS += \
    game-map-utils.h \
    random-utils.h
