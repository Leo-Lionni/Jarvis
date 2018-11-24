/*-*- coding: utf-8 -*-
 * Copyright (C) 2011 ~ 2018 Deepin, Inc.
 *               2011 ~ 2018 Wang Yong
 * Author:     Wang Yong <wangyong@deepin.com>
 * Maintainer: Wang Yong <wangyong@deepin.com>*/ 

#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <QAudioProbe>
#include <QDateTime>
#include <QEvent>
#include <QTimer>
#include <QWidget>

class Waveform : public QWidget
{
    Q_OBJECT

    static const int SAMPLE_DURATION;
    static const int WAVE_WIDTH;
    static const int WAVE_DURATION;

public:
    Waveform(QWidget *parent = 0);
    
    static qreal getPeakValue(const QAudioFormat &format);
    static QVector<qreal> getBufferLevels(const QAudioBuffer &buffer);

    template <class T>
    static QVector<qreal> getBufferLevels(const T *buffer, int frames, int channels);
                                                                                    
    void clearWave();
                                                                                    
public slots:
    void renderWave();
    void updateWave(float sample);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QDateTime lastSampleTime;
    QList<float> sampleList;
    QTimer *renderTimer;
};

#endif
