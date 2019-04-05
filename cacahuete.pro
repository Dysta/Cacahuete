#-------------------------------------------------
#
# Project created by QtCreator 2018-09-24T23:26:41
#
#-------------------------------------------------

QT       += core gui widgets network

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
INCLUDEPATH     += /usr/local/include/opencv2
LIBS            += -L/usr/local/include/opencv2 -lopencv_core \
                    -lopencv_highgui -lopencv_imgproc -lopencv_calib3d \
                    -lopencv_videoio -lopencv_video

SOURCES += main.cpp\
        mainwindow.cpp \
        utils.cpp \
        box/disparitybox.cpp \
        box/laplacianbox.cpp \
        box/sobelbox.cpp \
        box/calibdepthbox.cpp \
        process/disparityprocess.cpp \
        process/laplacianprocess.cpp \
        process/sobelprocess.cpp \
        process/calibdepthprocess.cpp \
        network.cpp \
    tracker.cpp

HEADERS  += mainwindow.h \
        utils.h \
        box/disparitybox.h \
        box/laplacianbox.h \
        box/sobelbox.h \
        box/calibdepthbox.h \
        process/disparityprocess.h \
        process/laplacianprocess.h \
        process/sobelprocess.h \
        process/calibdepthprocess.h \
        network.h \
    tracker.h

FORMS    += mainwindow.ui
