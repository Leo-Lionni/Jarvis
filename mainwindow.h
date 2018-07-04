#ifndef MAINWINDOW_H
#define MAINWINDOW_H

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavdevice/avdevice.h>
#include <libavfilter/avfilter.h>
#include <libavutil/avutil.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
}
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <QTimer>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString fileName;
private slots:
    void on_actionOpen_O_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
