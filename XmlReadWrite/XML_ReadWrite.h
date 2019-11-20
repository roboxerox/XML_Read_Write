#ifndef XML_ReadWrite_H
#define XML_ReadWrite_H
#include <QDomDocument>
#include <QObject>
#include <QMap>
#include <QFile>
#include <QXmlStreamWriter>
#include <QDebug>

enum XMLReadWrite_Error
{
    NoErrors,
    NotFound1,
    NotFound2,
    NotSetContent1,
    NotSetContent2,
    WritingError
};

class XML_ReadWrite : public QObject
{
    Q_OBJECT
public:
    QMap<QString,QString> Map_NodeValue;
signals:
    void Tag_Text(QString TagName, QByteArray Text);
    void Tag_NodeValue(QString TagName, QMap<QString,QString> NodeValue);
    void Errors(QString ErrorMsg);
public slots:
    bool SetXML_FileToRead(QString FileName);
    bool SetXML_QByteArrayToRead(QByteArray xml_data);
    void ReadXML_byQDomElement(QDomElement element);
    bool WriteNewXML_FileQByteArray(QString Directory,
                                    QString FileName,
                                    QByteArray xml_data);
    void ErrorDetails(XMLReadWrite_Error error);
    bool AppendXML_File(QString FileName,
                        QString ChildTagName,
                        QMap<QString, QString> ChildNodesValues,
                        QString ChildText,
                        QString ParentTagName,
                        QMap<QString, QString> ParentNodesValues);
};

#endif // XML_ReadWrite_H
