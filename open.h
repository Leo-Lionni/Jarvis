#ifndef OPEN_H
#define OPEN_H

#include <QObject>

class Open : public QThread
{
public:
    Open();
    void asHex();
    void asBin();
    void asASM();
    void asCode();
};

#endif // OPEN_H
