#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileName.clear();
    QAudioDeviceInfo a;
    qDebug()<<a.supportedCodecs();
}

QStringList MainWindow::getOutputDevice()
{//获取音频设备名称
        QStringList aDeviceListO;
        QList<QAudioDeviceInfo> audioDeviceListI =
                QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
        foreach (QAudioDeviceInfo devInfo, audioDeviceListI){
            QString strName = devInfo.deviceName();
            if (devInfo.isNull()) continue;
            if (strName[0] == 65533) continue;
            bool bFound = false;
            foreach (QString dev, aDeviceListO){
                if (strName == dev){
                    bFound = true;
                }
            }
            if (bFound == true) continue;
            aDeviceListO.push_back(strName);
            qDebug()<<strName;
        }
        return aDeviceListO;
}

MainWindow::~MainWindow()
{
    delete player;
    delete ui;
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
    if(fileName.isNull())
        qDebug()<<"Have nothing to play\nplease choose a playable file";
    QSoundEffect *login=new QSoundEffect(this);
    login->setSource(QUrl::fromLocalFile(fileName));  //主机上线音效
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
