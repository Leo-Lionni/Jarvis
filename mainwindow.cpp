#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileName.clear();
    fileName="test";
    player = new Audio(fileName);
    player->getOutputDevice();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete player;
}

void MainWindow::on_actionOpen_O_triggered()
{
    fileName=QFileDialog::getOpenFileName(this,tr("Open"),QString(),"*");
    if(!fileName.isEmpty()){
        qDebug()<<"fileName is:"<<fileName;
    }
}

void MainWindow::on_pushButtonPlay_clicked()
{
    qDebug()<<"play button clicked";
    if(fileName.isNull()) qDebug()<<"I have nothing to play\n"
                                    "please choose a playable file";
}

void MainWindow::on_pushButtonRecord_clicked()
{
    qDebug()<<"record button clicked";
}

void MainWindow::on_pushButtonStop_clicked()
{
    qDebug()<<"stop button clicked";
}

void MainWindow::on_pushButtonRcon_clicked()
{
    qDebug()<<"starting auto reconginatize audio files";
}
