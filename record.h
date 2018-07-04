#ifndef RECORD_H
#define RECORD_H
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
#include <iostream>
using namespace std;
class Record : public QThread
{
public:
    Record();
protected:
    void run();
};

#endif // RECORD_H
