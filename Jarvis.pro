QT                  += core gui widgets multimedia
INCLUDEPATH += $$PWD/ffmpeg/include/
win32{
LIBS += \
$$PWD/ffmpeg/lib/avcodec.lib \
$$PWD/ffmpeg/lib/avdevice.lib \
$$PWD/ffmpeg/lib/avfilter.lib \
$$PWD/ffmpeg/lib/avformat.lib \
$$PWD/ffmpeg/lib/avutil.lib \
$$PWD/ffmpeg/lib/postproc.lib \
$$PWD/ffmpeg/lib/swresample.lib \
$$PWD/ffmpeg/lib/swscale.lib
}
unix{
LIBS += \
$$PWD/ffmpeg/lib/libavcodec.dll.a \
$$PWD/ffmpeg/lib/libavdevice.dll.a \
$$PWD/ffmpeg/lib/libavfilter.dll.a \
$$PWD/ffmpeg/lib/libavformat.dll.a \
$$PWD/ffmpeg/lib/libavutil.dll.a \
$$PWD/ffmpeg/lib/libpostproc.dll.a \
$$PWD/ffmpeg/lib/libswresample.dll.a \
$$PWD/ffmpeg/lib/libswscale.dll.a
}
TARGET = Jarvis
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    audio.cpp

HEADERS += \
        mainwindow.h \
    audio.h

FORMS += \
        mainwindow.ui
