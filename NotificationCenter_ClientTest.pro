# qt
QT      += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = NotificationCenter_ClientTest
TEMPLATE = app

symbian {
	DEPLOYMENT.display_name = Notification Test Application
	VERSION                 = 1.0.0
	TARGET.UID3             = 0xAC928104
	TARGET.EPOCHEAPSIZE     = 0x20000 0x10000000

	LIBS += -lapgrfx -lapparc -lcone -leikcore -lavkon -lsisregistryclient -lws32
	LIBS += -lNotificationCenter_Client.lib
}

# sources
SOURCES += \
	src/Client.cpp

HEADERS += \
	src/Client.h \
	lib/NotificationCenter.h

RESOURCES += \
	qrc/Images.qrc

# compiler options
QMAKE_CXXFLAGS     += -std=c++0x

QMAKE_CXXFLAGS     += -Wall
QMAKE_CXXFLAGS     += -Wextra
QMAKE_CXXFLAGS     += -pedantic

greaterThan(QT_MAJOR_VERSION, 4) {
	QMAKE_CXXFLAGS += -Wdouble-promotion
}

QMAKE_CXXFLAGS     += -Wno-psabi
QMAKE_CXXFLAGS     += -Wno-invalid-offsetof
QMAKE_CXXFLAGS     += -fno-strict-aliasing

win32 {
	QMAKE_CXXFLAGS += -U__STRICT_ANSI__
}

CONFIG(release, debug|release) {
	QMAKE_CXXFLAGS += -O3
} else {
	QMAKE_CXXFLAGS += -O0
}
