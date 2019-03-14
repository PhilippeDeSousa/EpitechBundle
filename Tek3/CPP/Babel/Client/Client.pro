######################################################################
# Automatically generated by qmake (3.1) Wed Sep 26 15:10:54 2018
######################################################################

TEMPLATE = app
TARGET = Client
INCLUDEPATH += . \
                /usr/include/opus/
LIBS += -lopus \
        -lrt -lm -lasound -ljack -pthread -lportaudio \
        -lboost_system -lboost_thread

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_CXXFLAGS += -std=c++1z

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += MainWindow.hpp \
    Udpclient.hpp \
    AudioManager.hpp \
    StreamHandler.hpp \
    OpusHandler.hpp \
    PacketManager.hpp

FORMS += MainWindow.ui
SOURCES += Main.cpp MainWindow.cpp \
    Udpclient.cpp \
    AudioManager.cpp \
    StreamHandler.cpp \
    OpusHandler.cpp \
    PacketManager.cpp

RESOURCES +=

QT += widgets
QT += network

DISTFILES +=