QT += core gui widgets

TARGET = QRocketLaunchSimulator
TEMPLATE = app

include (../QRocketLaunchSimulator.pri)

LIBS += -L$$QROCKETLAUNCHSIMULATOR_BIN
LIBS += -lQRocketLaunchSimulator

INCLUDEPATH += $$QROCKETLAUNCHSIMULATOR_LIB

OBJECTS_DIR = $$QROCKETLAUNCHSIMULATOR_OBJ_GUI
MOC_DIR= $$QROCKETLAUNCHSIMULATOR_MOC_GUI

SOURCES += main.cpp \
    mainwindow.cpp \
    parameterwidget.cpp \
    rocketwidget.cpp \
    flightwidget.cpp

HEADERS  += \ 
    mainwindow.hpp \
    parameterwidget.hpp \
    rocketwidget.hpp \
    launchparameters.hpp \
    flightwidget.hpp
