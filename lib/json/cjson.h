#ifndef CJSON_H
#define CJSON_H
#include <QString>
#include <QMap>
#include "../utils.h"

class CJSON
{
public:
    CJSON(QString s);
    QString get(QString key);
    //QString getArray(QString key);
    //QString getObject(QString key);
private:
    void _parse(QString s);
    QMap <QString,QString> _flatData;
    QString operator[](const QString &s);
    //QMap <QString,CJSON*> _objects;
    //QMap <QString,CJSONArray*> _arrays
    Utils lib;

};

#endif // CJSON_H
