#ifndef __INIFILE_H__
#define __INIFILE_H__

// place your code here
#include <QMap>
#include "utils.h"
class IniFile{
public:
	IniFile(QString fullfilename = "");
        void loadFile(QString fullfilename);
        QMap<QString, QString> load();
	QString operator[](const QString &s);
        void save();
        void insert(QString key, QString value);

        bool success;
        QString file;
private:
        Utils lib;
	QMap <QString, QString> _return;

};
#endif // __INIFILE_H__
