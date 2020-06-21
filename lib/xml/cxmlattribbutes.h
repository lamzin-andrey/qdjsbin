#ifndef CXMLATTRIBBUTES_H
#define CXMLATTRIBBUTES_H

#include <QStringList>
#include <QString>

class CXmlAttribbutes
{
public:
    CXmlAttribbutes();
    void addAttribute(QString name, QString value = "CXmlAttibutes_UNDEFINED_VALUE_2016_21-08");
    QString getByName(QString name);
    int length();
    int _length;

    QStringList names;
    QStringList values;
    QString UNDEFINED_VALUE;

};

#endif // CXMLATTRIBBUTES_H
