#ifndef OCR_H
#define OCR_H

#include <QObject>
#include <QThread>
#include <QString>

class OCR : public QThread
{
public:
    OCR();
    void pdf();
    void pic();
    void toTXT();
    void toPDF();
    void toDOCX();
    void toPIC();
};

#endif // OCR_H
