QT -= gui widgets

TARGET = tests
TEMPLATE = app

include (../QRocketLaunchSimulator.pri)
include (../gtest.pri)
include (../gmock.pri)

INCLUDEPATH += ..

LIBS += -L$$QROCKETLAUNCHSIMULATOR_BIN
LIBS += -lQRocketLaunchSimulator

INCLUDEPATH += $$QROCKETLAUNCHSIMULATOR_LIB

OBJECTS_DIR = $$QROCKETLAUNCHSIMULATOR_OBJ_TESTS
MOC_DIR= $$QROCKETLAUNCHSIMULATOR_MOC_TESTS

SOURCES += main.cpp \
    test_rocketmodel.cpp \
    test_rocket.cpp
