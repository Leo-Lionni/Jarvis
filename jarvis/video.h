#ifndef VIDEO_H
#define VIDEO_H

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavdevice/avdevice.h>
#include <libavfilter/avfilter.h>
#include <libavutil/avutil.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
}
#include <QFile>
#include <QString>
#include <QDir>
#include <QTimer>
#include <QDebug>
#include <QThread>

class Video : public QThread
{
public:
    explicit Video(QString filename=NULL);
    bool isValuable();
    QString filename;
protected:
    void run();
};

#endif // VIDEO_H
