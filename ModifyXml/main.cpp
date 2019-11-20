#include <QCoreApplication>
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include <QDomDocument>

QDomDocument doc;
QDomElement root;

void ReadXML_byQDomElement(QDomElement element)
{
    while(!element.isNull())
    {
        qDebug()<<"Attributes "<<element.attributes().isEmpty() <<element.attributes().count()
               <<element.tagName();
        if(element.attributes().isEmpty())
        {
            qDebug()<<element.tagName()<<" "<<element.text();
            if(element.tagName()=="TAGsub1")
            {

                // create a new node with a QDomText child
                QDomElement newNodeTag = doc.createElement(QString("TAGsub1"));
                QDomText newNodeText = doc.createTextNode(QString("888"));
                newNodeTag.appendChild(newNodeText);

                // replace existing node with new node
                element.parentNode().replaceChild(newNodeTag, element);
                qDebug()<<"new  "<<newNodeTag.tagName()<<newNodeTag.text();
                //set current element
                element = newNodeTag;
            }
            if(element.tagName()=="TAGsub2")
            {

                // create a new node with a QDomText child
                QDomElement newNodeTag = doc.createElement(QString("TAGsub2"));
                QDomText newNodeText = doc.createTextNode(QString("111"));
                newNodeTag.appendChild(newNodeText);

                // replace existing node with new node
                element.parentNode().replaceChild(newNodeTag, element);
                qDebug()<<"new  "<<newNodeTag.tagName()<<newNodeTag.text();
                //set current element
                element = newNodeTag;
            }
        }
        else // if node has attributes
        {
            for(int i=0;i<element.attributes().count();i++)
                qDebug()<<" "<<element.attributes().item(i).nodeName()<<" "<<element.attributes().item(i).nodeValue();
        }

        if(element.hasChildNodes())
        {
            QDomElement child = element.firstChildElement();
            ReadXML_byQDomElement(child);
        }
        element=element.nextSiblingElement();
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QByteArray array;
    QFile file("/path to/textxml.xml");
    if(file.open(QIODevice::ReadWrite))
        array = file.readAll();

    doc.setContent(array);

    root = doc.documentElement();

   ReadXML_byQDomElement(root);

    // Write changes to same file
    file.resize(0);
    QTextStream stream;
    stream.setDevice(&file);
    doc.save(stream, 4);

    file.close();


    return a.exec();
}
