#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <QTimer>
#include <QDebug>
#include <QTextCodec>
#include "audio.h"

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
    void on_pushButtonPlay_clicked();
    void on_pushButtonRecord_clicked();
    void on_pushButtonStop_clicked();
    void on_pushButtonRcon_clicked();
public:
    Audio *player;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
