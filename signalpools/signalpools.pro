#-------------------------------------------------
#
# Project created by QtCreator 2016-06-27T09:54:56
#
#-------------------------------------------------
QT       -= gui

#TARGET = signalpools
TEMPLATE = lib

DEFINES += SIGNALPOOLS_LIBRARY

CONFIG(debug debug|release)
{
    TARGET = SignalPoolsd
}
CONFIG(release debug|release)
{
    TARGET = SignalPools
}

SOURCES += signalpools.cpp \
    safepublisher.cpp \
    safesignalmanager.cpp \
    safesignalpools.cpp \
    safesubscriber.cpp \
    signalpublish.cpp \
    signalsubscribe.cpp \
    signalmanager.cpp

HEADERS += signalpools.h\
    safepublisher.h \
    safesignalmanager.h \
    safesignalpools.h \
    safesubscriber.h \
    signalpools_global.h \
    signalpublish.h \
    signalsubscribe.h \
    signalmanager.h
