#-------------------------------------------------
#
# Project created by QtCreator 2020-11-13T09:43:59
#
#-------------------------------------------------

QT       += core gui network axcontainer webkit webkitwidgets multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
    Mpeg_Player.cpp \
    Mainwindow.cpp \
    SWFPlayer.cpp \
    HTMLEdit.cpp \
    exercise_treeview.cpp

HEADERS  += \
    Mpeg_Player.h \
    Mainwindow.h \
    SWFPlayer.h \
    HTMLEdit.h \
    exercise_treeview.h

FORMS    += mainwindow.ui \
    mpeg_player.ui
