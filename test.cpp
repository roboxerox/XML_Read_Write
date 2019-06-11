#include "test.h"

Test::Test()
{
    XML_ReadWrite * xml = new XML_ReadWrite;
    connect(xml,SIGNAL(Tag_NodeValue(QString,QMap<QString,QString>)),this,SLOT(Print2(QString,QMap<QString,QString>)));
    connect(xml,SIGNAL(Tag_Text(QString,QByteArray)),this,SLOT(Print1(QString,QByteArray)));
    connect(xml,SIGNAL(Errors(QString)),this,SLOT(ERROR(QString)));
    xml->SetXML_FileToRead("/opt/smart_coach/temp/26_P001/000/Entry Periphery/034/NewData.xml");    //this xml file has tag type is <TAG>text</TAG>
    xml->SetXML_FileToRead("/home/apaul/XML_ReadWrite/mcu_stat.xml");                                //this xml file has tag type is <TAG Node1="value1" Node2="Value2"/>
    xml->SetXML_QByteArrayToRead(QByteArray("<TAG><Tag1><Tag2>Text2</Tag2></Tag1><Tag3>Text3</Tag3></TAG>"));
    //xml->WriteXML_FileQByteArray("/home/apaul/XML_ReadWrite","Tag",QByteArray("<TAG>\n<Tag1>\n<Tag2>Text2</Tag2>\n</Tag1>\n<Tag3>Text3</Tag3>\n</TAG>"));
    QMap<QString,QString> P,P2;
    P.insert("EtuOnline","2");
    P.insert("EtuSelected","0");
    P.insert("EtuState","OK");
    QMap<QString,QString> C,C1 , C2;
    C.insert("IP","192.168.0.1");
    C.insert("COACH","123");
    C2.insert("Mode","ETU");
    C2.insert("GSMSTAT","Online");
    xml->AppendXML_File("/home/apaul/XML_ReadWrite/mcu_stat.xml","ETUS",C,"","ETUSTAT", P);
    xml->AppendXML_File("/home/apaul/XML_ReadWrite/mcu_stat.xml","ETUS",C,"","ETUSTAT", P2);
    xml->AppendXML_File("/home/apaul/XML_ReadWrite/mcu_stat.xml","STATHEADER",C2,"","", P2);
    xml->AppendXML_File("/home/apaul/XML_ReadWrite/Tag.xml","INC1",C1,"Coach012","OPT", P2);
    xml->AppendXML_File("/home/apaul/XML_ReadWrite/Tag.xml","INC2",C1,"Coach022","", P2);


    qDebug()<<"0000000000000000000";
    xml->SetXML_QByteArrayToRead(QByteArray("<TAG><Tag1>&lt;Tag2&gt;Text2&lt;/Tag2&gt;</Tag1><Tag3>Text3</Tag3></TAG>"));
//    QXmlStreamReader reader;
//    //reader.setDevice(&file);
//    reader.addData(QByteArray("<TAG><Tag1>&lt;Tag2&gt;Text2&lt;/Tag2&gt;</Tag1><Tag3>Text3</Tag3></TAG>"));
//    while (!reader.atEnd() && !reader.hasError())
//    {
//        reader.readNext();

//            qDebug()<<reader.name()<<" : "<<reader.readElementText();

//    }
    qDebug ()<<"Num "<<QString::number(2).rightJustified(2,'0');

    qDebug ()<<"NUM " << QByteArray("PSX00214").mid(0,3);


//    QString text =
//                "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do\n"
//                "eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut\n"
//                "enim ad minim veniam, quis nostrud exercitation ullamco laboris\n"
//                "nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor\n"
//                "in reprehenderit in voluptate velit esse cillum dolore eu fugiat\n"
//                "nulla pariatur. Excepteur sint occaecat cupidatat non proident,\n"
//                "sunt in culpa qui officia deserunt mollit anim id est laborum.\n";

//        QPrinter printer;

//        QPrintDialog *dialog = new QPrintDialog(&printer);
//        dialog->setWindowTitle("Print Document");

//        if (dialog->exec() != QDialog::Accepted)
//            return -1;
//            qDebug()<<"000000000";

//        QPainter painter;
//        painter.begin(&printer);

//        painter.drawText(100, 100, 500, 500, Qt::AlignLeft|Qt::AlignTop, text);

//        painter.end();


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
