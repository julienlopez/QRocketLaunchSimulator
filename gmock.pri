GMOCK_PATH =

isEmpty(GMOCK_PATH) {
}
else {
	INCLUDEPATH += $$GMOCK_PATH/include
	LIBS += -L$$GMOCK_PATH/lib/.libs
}

LIBS += -lgmock
