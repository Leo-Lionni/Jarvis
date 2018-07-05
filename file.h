#ifndef FILE_H
#define FILE_H

#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QFileDevice>
#include <QFileDialog>
#include <QString>
#include <QIODevice>
#include <QThread>
#include <QTextStream>
#include <QTextCodec>

class File : public QThread
{
public:
    File();
    void changeCodecto(QString codecName);
    void Assember();
    void removeNextLine();
};

#endif // FILE_H
