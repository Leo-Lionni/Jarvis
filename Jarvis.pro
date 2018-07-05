QT       += core gui widgets multimedia

TARGET = Jarvis
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
LIBS += -L /usr/local/lib -lavformat -lavcodec -lavutil \
        -lswresample -lopencv_core -lopencv_gpu -lopencv_photo \
        -lopencv_video -lswscale -lSDL2
SOURCES += \
        main.cpp \
        mainwindow.cpp \
    audio.cpp \
    video.cpp \
    record.cpp \
    waveform.cpp \
    picture.cpp \
    ocr.cpp \
    open.cpp \
    file.cpp \
    regexp.cpp \
    highlighter.cpp \
    svm.cpp \
    voice.cpp \
    codeparser.cpp

HEADERS += \
        mainwindow.h \
    audio.h \
    video.h \
    record.h \
    waveform.h \
    picture.h \
    ocr.h \
    open.h \
    file.h \
    regexp.h \
    highlighter.h \
    svm.h \
    voice.h \
    codeparser.h

FORMS += \
        mainwindow.ui
