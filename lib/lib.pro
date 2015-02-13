QT -= gui widgets

TARGET = QRocketLaunchSimulator
TEMPLATE = lib

include (../QRocketLaunchSimulator.pri)

INCLUDEPATH += ..

OBJECTS_DIR = $$QROCKETLAUNCHSIMULATOR_OBJ_LIB
MOC_DIR= $$QROCKETLAUNCHSIMULATOR_MOC_LIB

SOURCES += \ 
    rocketmodel.cpp \
    stagemodel.cpp \
    ../external/json.cc \
    utils/json_helper.cpp \
    rocket.cpp \
    stage.cpp \
    fairings.cpp

HEADERS  += \ 
    rocketmodel.hpp \
    ../external/json.h \
    stagemodel.hpp \
    utils/json_helper.hpp \
    rocket.hpp \
    stage.hpp \
    fairings.hpp
