#ifndef AUDIO_H
#define AUDIO_H

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
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL.h>

#define MAX_AUDIO_FRAME_SIZE 192000 // 1 second of 48khz 32bit audio

//Output PCM
#define OUTPUT_PCM 1
//Use SDL
#define USE_SDL 1

//Buffer:
//|-----------|-------------|
//|chunk------pos---len-----|
static  Uint8  *audio_chunk;
static  Uint32  audio_len;
static  Uint8  *audio_pos;

class Audio : public QThread
{
public:
    Audio(QString filename="NULL");
    bool isValuable();
    bool RetriveAudio(QString filename);
    bool getFrame(QString filename);
    void fill_audio(Uint8 *stream, int len);
    QString filename;
protected:
    void run();
};

#endif // AUDIO_H
