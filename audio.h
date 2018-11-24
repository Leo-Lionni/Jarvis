#ifndef AUDIO_H
#define AUDIO_H

#include <QAudioDeviceInfo>
#include <QAudio>
#include <QVector>
#include <QFile>
#include <QString>
#include <QDir>
#include <QDataStream>
#include <QTimer>
#include <QDebug>
#include <QThread>
#include <QIODevice>
#include <QApplication>

#define __STDC_CONSTANT_MACROS
extern "C" {
   #include <libavcodec/avcodec.h>
   #include <libavformat/avformat.h>
   #include <libavdevice/avdevice.h>
   #include <libavfilter/avfilter.h>
   #include <libavutil/avutil.h>
   #include <libswresample/swresample.h>
   #include <libswscale/swscale.h>
}
#define MAX_AUDIO_FRAME_SIZE 192000 // 1 second of 48khz 32bit audio
//Output PCM
#define OUTPUT_PCM 1
//Buffer:
//|-----------|-------------|
//|chunk------pos---len-----|

class Audio : public QThread
{
public:
    Audio(QString filename);
    bool isValuable();
    bool RetriveAudio(QString filename);
    bool getFrame(QString filename);
    bool decoder(QString input,QString output);
    bool encoder(QString input,QString output);
    QString                filename;
    QFile                    file;
    AVOutputFormat   *ofmt;
    AVFormatContext	*pFormatCtx;
    unsigned int          i, audioStream;
    AVCodecContext    *pCodecCtx;
    AVCodec			    *pCodec;
    AVPacket		        *packet;
    uint8_t			        *out_buffer;
    AVFrame			    *pFrame;
    int                         ret;
    int                         got_picture;
    int                         index = 0;
    int64_t                   in_channel_layout;
    struct SwrContext   *au_convert_ctx;
    void run();
};

#endif // AUDIO_H
