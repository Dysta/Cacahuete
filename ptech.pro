#-------------------------------------------------
#
# Project created by QtCreator 2018-09-24T23:26:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ptech
TEMPLATE = app

# Redirect tmp file
OBJECTS_DIR = ./tmp/obj
MOC_DIR = ./tmp/moc

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


# Including the opencv2 lib
INCLUDEPATH     += /usr/include/opencv2
LIBS            += -L/usr/include/opencv2 -lopencv_core -lopencv_highgui -lopencv_imgproc

SOURCES += main.cpp\
        mainwindow.cpp \
    converter.cpp

HEADERS  += mainwindow.h \
    converter.h

FORMS    += mainwindow.ui