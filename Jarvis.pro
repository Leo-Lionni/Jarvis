QT                  += core gui widgets multimedia
INCLUDEPATH += \
$$PWD/armadillo/ \
$$PWD/FFmpeg/include/ \
$$PWD/OpenCV/include/ \
$$PWD/SDL/include/ \
$$PWD/x264/include/
unix{
LIBS += -L$$PWD/armadillo/ \
-L$$PWD/engines/ \
-L$$PWD/FFmpeg/lib/ \
-L$$PWD/OpenCV/lib/ \
-L$$PWD/SDL/lib \
-L$$PWD/x264/lib \
-larmadillo \
-lopencv_core -lopencv_highgui -lopencv_video -lopencv_dnn \
-lSDL2 -lx264 \
-lavcodec -lavdevice -lavfilter -lavformat -lavutil -lpostproc \
-lswscale -lswresample
}
TARGET = Jarvis
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        mainwindow.cpp \

HEADERS += \
        mainwindow.h \

FORMS += \
        mainwindow.ui
