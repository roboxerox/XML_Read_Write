#ifndef TEST_H
#define TEST_H
#include <XML_ReadWrite.h>
#include <QtGlobal>
#include <QDebug>
#include <QFile>
#include <QPrinter>
#include <QPainter>
#include <QPrintDialog>
#include <QDir>
#include <QDateTime>

class Test :public QObject
{
    Q_OBJECT
public:
    Test();
private slots:
    void Print1(QString tag, QByteArray text);
    void Print2(QString tag, QMap<QString,QString> nodeval);
    void ERROR(QString text);


};

#endif // TEST_H
