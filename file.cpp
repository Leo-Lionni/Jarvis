#include "file.h"

File::File()
{

}

void File::removeNextLine()
{
    int i=0;
    QString outputfile=QDir::currentPath()+QDir::separator()+"adress.txt";
    QFile fileoutput(outputfile);
    if(!fileoutput.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)) return;
    QTextStream writeOut(&fileoutput);
    QString filename=":/adressTables.txt";
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"done";
        QTextStream readIn(&file);
        while(!readIn.atEnd()){
            QString temp=readIn.readLine();
            if(!temp.isEmpty()){
                writeOut<<temp+'\n';
                i++;
            }
        }
    }
    file.close();
    fileoutput.close();
}
