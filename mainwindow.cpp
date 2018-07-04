#include "audio.h"
#include "video.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<<"done";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_O_triggered()
{
    fileName=QFileDialog::getOpenFileName(this,tr("Open"),QString(),"*");
    if(!fileName.isEmpty()){
        qDebug()<<"fileName is:"<<fileName;
    }
    Video *video= new Video(fileName);
}
