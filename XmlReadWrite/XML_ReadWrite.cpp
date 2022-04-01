/********************************************************************************
 ** This file is part of Read & Write xml data to/from xml file
 **
 ********************************************************************************/
#include "XML_ReadWrite.h"

/**
 * @brief XML_ReadWrite::ReadXML_File
 * @param FileName  : String name of file
 * This slot set file to QDomDocument content
 * and pass QDomElement to slot ReadXML_byQDomElement()
 */
bool XML_ReadWrite::SetXML_FileToRead(QString FileName)
{
    QFile file(FileName);
    if(file.exists())
    {
        QDomDocument *doc = new QDomDocument;
        if (!doc->setContent(&file))
        {
            file.close();
            ErrorDetails(XMLReadWrite_Error::NotSetContent1);
            return false;
        }
        else
        {
            file.close();
            ReadXML_byQDomElement(doc->documentElement());
            return true;
        }
    }
    else
        ErrorDetails(XMLReadWrite_Error::NotFound1);
    return false;
}
/**
 * @brief XML_ReadWrite::ReadXML_QByteArray
 * @param xml_data  : ByteArray of xml format data
 * This slot set ByteArray to QDomDocument content
 * and pass QDomElement to slot ReadXML_byQDomElement()
 */
bool XML_ReadWrite::SetXML_QByteArrayToRead(QByteArray xml_data)
{
    QDomDocument *doc = new QDomDocument;
    xml_data.replace("&lt;","<");
    xml_data.replace("&gt;",">");
    if (!doc->setContent(xml_data))
    {
        ErrorDetails(XMLReadWrite_Error::NotSetContent2);
        return false;
    }
    else
        ReadXML_byQDomElement(doc->documentElement());
    return true;
}
/**
 * @brief XML_ReadWrite::ReadXML_byQDomElement
 * @param element :DomElement
 * This slot Read Tag Name & its Text or NodeName and NodeValue while file is not reached end.
 * If Tag has Node & value it emit signal with tag name and QMap of Node and value
 * Tag example <Tag Node1=value1 Node2=value2 />
 * If Tag name has Text(not nodes & values) emit signal with tag name and its text
 * Tag example <Tag>text</Tag>
 */
void XML_ReadWrite::ReadXML_byQDomElement(QDomElement element)
{
    while(!element.isNull())
    {
        qDebug()<<"Attributes "<<element.attributes().isEmpty() <<element.attributes().count()
               <<element.tagName();
        if(element.attributes().isEmpty())
            emit Tag_Text(element.tagName(),element.text().toUtf8());
        else
        {
            Map_NodeValue.clear();
            for(int i=0;i<element.attributes().count();i++)
                Map_NodeValue.insert(element.attributes().item(i).nodeName(),element.attributes().item(i).nodeValue());
            emit Tag_NodeValue(element.tagName(),Map_NodeValue);
        }

        if(element.hasChildNodes())
        {
            QDomElement child = element.firstChildElement();
            ReadXML_byQDomElement(child);
        }
        element=element.nextSiblingElement();
    }
}
/**
 * @brief XML_ReadWrite::WriteXML_FileQByteArray
 * @param Dir       : directory name
 * @param FileName  : file name
 * @param xml_data  : ByteArray xml data
 * This slot create & write a xml file with xml_data
 */
bool XML_ReadWrite::WriteNewXML_FileQByteArray(QString Directory, QString FileName, QByteArray xml_data)
{
    if(!QFile(Directory).exists())
    {
        ErrorDetails(XMLReadWrite_Error::NotFound2);
        return false;
    }
    else
    {
        QFile file(Directory+"/"+FileName+".xml");

        if(file.open(QIODevice::ReadWrite))
        {
            QXmlStreamWriter xmlWriter(&file);
            xmlWriter.setCodec("UTF-8");
            xmlWriter.setAutoFormatting(true);
            xmlWriter.writeStartDocument();
            xmlWriter.writeCharacters("\n");
            xmlWriter.device()->write(xml_data.constData(), xml_data.length());
            xmlWriter.writeEndElement();

            ErrorDetails(XMLReadWrite_Error::NoErrors);
            file.close();
            return true;
        }
        else
            ErrorDetails(XMLReadWrite_Error::WritingError);
    }

    return false;
}
/**
 * @brief XML_ReadWrite::ErrorDetails
 * @param error  : num types of error
 * This slot show details of Error types
 */
void XML_ReadWrite::ErrorDetails(XMLReadWrite_Error error)
{
    switch (error)
    {
    case XMLReadWrite_Error::NoErrors:
        emit Errors("No Errors.");
        break;
    case XMLReadWrite_Error::NotFound1:
        emit Errors("XML file not found.");
        break;
    case XMLReadWrite_Error::NotFound2:
        emit Errors("Directory not found.");
        break;
    case XMLReadWrite_Error::NotSetContent1:
        emit Errors("File not set to content. Xml data content has error.");
        break;
    case XMLReadWrite_Error::NotSetContent2:
        emit Errors("QByteArray not set to content. Xml data content has error.");
        break;
    case XMLReadWrite_Error::WritingError:
        emit Errors("Error in Writting data.");
        break;
    default:
        break;
    }
}
/**
 * @brief XML_ReadWrite::AppendXML_File
 * This slot append existing xml file
 * @param FileName          : XML file name
 * @param ChildTagName      : Child tag name
 * @param ChildNodesValues  : it will be null , if child tag tpye is <TAG>text</TAG>
 * @param ChildText         : it will be null if child tag tpye is <TAG Node0="Value0", Node1="value1" />
 * @param ParentTagName     : Parent tag name  it may be use or not in xml
 * @param ParentNodesValues : it will be null , if Parent tag tpye is <TAG><tag1>text<tag1></TAG>
 */
bool XML_ReadWrite::AppendXML_File(QString FileName, QString ChildTagName, QMap<QString, QString> ChildNodesValues,
                                   QString ChildText, QString ParentTagName, QMap<QString, QString> ParentNodesValues)
{

    QFile file(FileName);
    if(file.exists())
    {
        file.open(QIODevice::ReadWrite);

        QDomDocument *doc = new QDomDocument;
        if (!doc->setContent(file.readAll()))
        {
            file.close();
            ErrorDetails(XMLReadWrite_Error::NotSetContent1);
        }
        else
        {
            QDomElement root = doc->documentElement();
            QDomElement ChildTag = doc->createElement(ChildTagName);
            QDomText Child_Text;
            if(ParentTagName!="")
            {
                QDomElement ParentTag = doc->createElement(ParentTagName);
                if(ParentNodesValues.size()>0)
                {
                    QMap<QString, QString>::iterator ParentMap;
                      for (ParentMap = ParentNodesValues.begin(); ParentMap != ParentNodesValues.end(); ++ParentMap)
                          ParentTag.setAttribute(ParentMap.key(),ParentMap.value());
                }
                if(ChildNodesValues.size()>0)
                {
                    QMap<QString, QString>::iterator childMap;
                      for (childMap = ChildNodesValues.begin(); childMap != ChildNodesValues.end(); ++childMap)
                          ChildTag.setAttribute(childMap.key(),childMap.value());
                }
                else
                {
                    Child_Text = doc->createTextNode(ChildText);
                    ChildTag.appendChild(Child_Text);
                }

                ParentTag.appendChild(ChildTag);
                root.appendChild(ParentTag);
            }
            else
            {
                if(ChildNodesValues.size()>0)
                {
                    QMap<QString, QString>::iterator childMap;
                      for (childMap = ChildNodesValues.begin(); childMap != ChildNodesValues.end(); ++childMap)
                          ChildTag.setAttribute(childMap.key(),childMap.value());
                }
                else
                {
                    Child_Text = doc->createTextNode(ChildText);
                    ChildTag.appendChild(Child_Text);
                }

                 root.appendChild(ChildTag);
            }
            file.resize(0);
            QTextStream stream(&file);
            stream.setDevice(&file);
            doc->save(stream, 4);
            file.close();
            return true;
        }
    }
    else
        ErrorDetails(XMLReadWrite_Error::NotFound1);

    return false;
}
