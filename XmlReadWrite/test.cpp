#include "test.h"

Test::Test()
{
    XML_ReadWrite * xml = new XML_ReadWrite;
    connect(xml,SIGNAL(Tag_NodeValue(QString,QMap<QString,QString>)),this,SLOT(Print2(QString,QMap<QString,QString>)));
    connect(xml,SIGNAL(Tag_Text(QString,QByteArray)),this,SLOT(Print1(QString,QByteArray)));
    connect(xml,SIGNAL(Errors(QString)),this,SLOT(ERROR(QString)));

    qDebug()<<QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")<<__FUNCTION__ <<"***Type 1 Read xml";
    xml->SetXML_FileToRead(QDir::currentPath()+"/../xmls/NewData.xml");    //this xml file has tag type is <TAG>text</TAG>

    qDebug()<<QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")<<__FUNCTION__ <<"***Type 2 Read xml";
    xml->SetXML_FileToRead(QDir::currentPath()+"/../xmls/sip_stat.xml");                                //this xml file has tag type is <TAG Node1="value1" Node2="Value2"/>

    qDebug()<<QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")<<__FUNCTION__ <<"***Type 3 Read xml";
    xml->SetXML_QByteArrayToRead(QByteArray("<TAG><Tag1><Tag2>Text2</Tag2></Tag1><Tag3>Text3</Tag3></TAG>"));
    //xml->WriteXML_FileQByteArray(QDir::currentPath()+"/../xmls","Tag",QByteArray("<TAG>\n<Tag1>\n<Tag2>Text2</Tag2>\n</Tag1>\n<Tag3>Text3</Tag3>\n</TAG>"));


    QMap<QString,QString> P,P2;
    P.insert("sipOnline","2");
    P.insert("sipSelected","0");
    P.insert("sipState","OK");
    QMap<QString,QString> C,C1 , C2;
    C.insert("IP","192.168.0.1");
    C.insert("LOC","123");
    C2.insert("Mode","SIP");
    C2.insert("GSMSTAT","Online");

    qDebug()<<QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")<<__FUNCTION__ <<"***Type 1 Append xml";
    xml->AppendXML_File(QDir::currentPath()+"/../xmls/sip_stat.xml","SIP",C,"","SIP_STAT", P);
    qDebug()<<QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")<<__FUNCTION__ <<"***Type 2 Append xml";
    xml->AppendXML_File(QDir::currentPath()+"/../xmls/sip_stat.xml","SIP",C,"","SIP_STAT", P2);
    qDebug()<<QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")<<__FUNCTION__ <<"***Type 3 Append xml";
    xml->AppendXML_File(QDir::currentPath()+"/../xmls/sip_stat.xml","STATHEADER",C2,"","", P2);
    qDebug()<<QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")<<__FUNCTION__ <<"***Type 4 Append xml";
    xml->AppendXML_File(QDir::currentPath()+"/../xmls/Tag.xml","INC1",C1,"Loc012","OPT", P2);
    qDebug()<<QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")<<__FUNCTION__ <<"***Type 5 Append xml";
    xml->AppendXML_File(QDir::currentPath()+"/../xmls/Tag.xml","INC2",C1,"Loc022","", P2);


    qDebug()<<QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")<<__FUNCTION__ <<"***Type 4 Read xml";
    xml->SetXML_QByteArrayToRead(QByteArray("<TAG><Tag1>&lt;Tag2&gt;Text2&lt;/Tag2&gt;</Tag1><Tag3>Text3</Tag3></TAG>"));
//    QXmlStreamReader reader;
//    //reader.setDevice(&file);
//    reader.addData(QByteArray("<TAG><Tag1>&lt;Tag2&gt;Text2&lt;/Tag2&gt;</Tag1><Tag3>Text3</Tag3></TAG>"));
//    while (!reader.atEnd() && !reader.hasError())
//    {
//        reader.readNext();

//            qDebug()<<reader.name()<<" : "<<reader.readElementText();

//    }

}
void Test::ERROR(QString text)
{
    qDebug()<<"Error "<<text;
}

void Test::Print1(QString tag, QByteArray text)
{
    qDebug()<<"TAG : "<<tag;
    qDebug()<<"  Text :"<<text;
}

void Test::Print2(QString tag, QMap<QString, QString> nodeval)
{
    qDebug()<<"TAG : "<<tag;
    qDebug()<<"  Keys : "<<nodeval.keys();
    qDebug()<<"  values :"<<nodeval.values();
}
