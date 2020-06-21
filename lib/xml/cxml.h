#ifndef CXML_H
#define CXML_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QList>
#include <QRegExp>

#include "cxmlattribbutes.h"
#include "../utils.h"

class CXml
{
public:
    CXml(QString file = "", CXml* parent = 0, bool isSingleTag = false);
    bool setXmlText(QString xml);
    bool isNotPipe(QChar ch);

    QList<CXml*> childs;
    bool success;
    bool _isSingleTag;
    QStringList log;

    QString tagName;
    QString innerXML;
    QString ROOT;
    CXml *parentNode;
    CXmlAttribbutes* attributes;

    QList<CXml*> getElementsByTagName(QString tagName);
    QString getAttribute(QString title);

private:
    Utils lib;

    QString _trim(QString s);
    QString _getCloseTagName(QString xml, int pos);
    QString _getOpenTagName(QString currentTagName, QString def);
    QString _closeCurrentTag(QString currentTagName, QString closeTagName, QString def, int &level);
    QString _parseTag(QString s);
    QString _grabNoPairTags(QString xml, QString def, QString tags);
    int _indexOf(QString xml, QChar needle, int pos);
    int _lastIndexOf(QString xml, QChar needle, int pos);
    QString _extractOpenTagName(QString xml, int pos);
    void _parseAttributes(QString xml, QString tagName, int length);

    int rDebug;

};

#endif // CXML_H



