QT                  += core gui widgets multimedia
INCLUDEPATH += \
$$PWD/lib/armadillo/ \
$$PWD/lib/FFmpeg/include/ \
$$PWD/lib/OpenCV/include/ \
$$PWD/lib/SDL/include/ \
$$PWD/lib/x264/include/
unix{
LIBS += -L$$PWD/lib/armadillo/ \
-L$$PWD/lib/FFmpeg/lib/ \
-L$$PWD/lib/OpenCV/lib/ \
-L$$PWD/lib/SDL/lib \
-L$$PWD/lib/x264/lib \
-larmadillo \
-lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_dnn \
-lSDL2 -lx264 \
-lavcodec -lavdevice -lavfilter -lavformat -lavutil -lpostproc \
-lswscale -lswresample
}
TARGET = Jarvis
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = bin
OBJECTS_DIR = tmp/obj
MOC_DIR = tmp/moc
UI_DIR = tmp/ui
RCC_DIR = tmp/rcc

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    video.cpp \
    audio.cpp \
    waveform.cpp \
    record.cpp

HEADERS += \
        mainwindow.h \
    record.h \
    audio.h \
    video.h \
    waveform.h

FORMS += \
        mainwindow.ui
