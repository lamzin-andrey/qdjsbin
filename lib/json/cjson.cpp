#include "cjson.h"

CJSON::CJSON(QString s)
{
    _parse(s);
}

void CJSON::_parse(QString s) {
    s = s.trimmed();
    bool inStr = false;
    bool inKey = true;
    bool inVal = false;
    QString key = "";
    QString val = "";
    QChar ch;
    if (s[0] == '{' && s[s.length() - 1] == '}') {
      for (unsigned int i = 1; i < s.length() - 1; i++) {
          ch = s[i];
          //инициализация состояния
          if (!inStr && ch == '"') {
              inStr = true;
              continue;
          }
          if (!inStr && ch == ':') {
              inKey = false;
              inVal = true;
          }
          if (!inStr && ch == ',') {
              inKey = true;
              inVal = false;
              //lib.qMessageBox("Append", "key=" + key + ", val=" + val);
              _flatData[key] = val;
              key = val = "";
          }
          if (inStr && ch == '"' && (i - 1) > 0 && s[i - 1] != '\\') {
              inStr = false;
              continue;
          }

          //логика
          if (inStr && inKey) {
              key += ch;
              //lib.qMessageBox("Append char to key", "key=" + key + ", val=" + val);
          }
          if (inStr && inVal) {
              val += ch;
              //lib.qMessageBox("Append char to val", "key=" + key + ", val=" + val);
          }
          /*if (!inStr && inVal && ch == '[') {
              i = _parseAndAddArray(i, key, s);//TODO вернит положение следующего после закрывающей ] символа или  -1 если вышли за пределы тела
              key = "";
              val = "";
              continue;
          }
          if (!inStr && inVal && ch == '{') {
              i = _parseAndAddObject(i, key, s);//TODO вернит положение следующего после закрывающей ] символа или  -1 если вышли за пределы тела
              key = "";
              val = "";
              continue;
          }*/
      }
      if (key.length() && val.length()) {
        _flatData[key] = val;
      }
    }
}

QString CJSON::get(QString key) {
    if (_flatData.contains(key)) {
        return _flatData[key];
    }
    return "";
}

QString CJSON ::  operator[](const QString &s)
{
    return _flatData[s];
}
