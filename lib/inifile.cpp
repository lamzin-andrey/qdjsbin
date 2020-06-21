#include "inifile.h"

// place your code here
IniFile :: IniFile(QString fullfilename){
        file = "";
        success = false;
        if (fullfilename != "") this->loadFile(fullfilename);
}
//-------------------------------------------
void IniFile :: loadFile(QString fullfilename)
{
    _return.clear();
    QString s = lib.readtextfile(fullfilename, true);
        if (s != ""){
                QStringList list = s.split("\n");
                for (int i = 0; i < list.size(); i++){
                        QStringList list2 = list[i].split("=");
                        if (list2.size() > 1)
                            _return.insert(list2[0], list2[1]);
                }
                file = fullfilename;
                success = true;
        }
}
//------------------------------------------
QMap <QString, QString> IniFile :: load(){
	return _return;
}
//-----------------------------------------
QString IniFile ::  operator[](const QString &s)
{
	return _return[s];
}
//-----------------------------------------
void IniFile :: save()
{
    QString content = "";
    QStringList arr;
    QList <QString> keys = _return.keys();
    for (int i = 0; i < this->_return.size(); i++)
    {
        arr << keys[i] + "=" + this->_return[keys[i]];
    }
    content = arr.join("\n");
    lib.writetextfile(file, content);
}

void IniFile :: insert(QString key, QString value)
{
    _return[key] = value;
}
