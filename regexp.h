#ifndef REGEXP_H
#define REGEXP_H

#include <QObject>
#include <QRegExp>
#include <QRegExpValidator>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

class RegExp : public QThread
{
public:
    RegExp();
};

#endif // REGEXP_H
