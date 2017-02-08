QT += core sql
QT -= gui

CONFIG += c++11

TARGET = SysTecTask
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    dbmanager.cpp \
    employee.cpp \
    manager.cpp \
    sales.cpp \
    ui.cpp

HEADERS += \
    dbmanager.h \
    employee.h \
    manager.h \
    sales.h \
    ui.h \
    iworker.h
