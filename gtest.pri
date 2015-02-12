GTEST_PATH =

isEmpty(GTEST_PATH) {
}
else {
	INCLUDEPATH += $$GTEST_PATH/include
	LIBS += -L$$GTEST_PATH/lib/.libs
}

LIBS += -lgtest
