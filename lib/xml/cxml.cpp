#include "cxml.h"

CXml::CXml(QString file, CXml* parent, bool isSingleTag){
    this->_isSingleTag = isSingleTag;
    rDebug = 0;
    this->innerXML = "";
    this->attributes = new CXmlAttribbutes();
    this->ROOT = "C_XML_2016_08_21_DOC_ROOT";

    QString s = lib.readtextfile(file, true);
    if (!s.length()) {
        s = file;
        //lib.writetextfile("log.log", "\nContent:\n" + s + "\n", true);
    }
    this->parentNode = parent;
    if (parent == 0) {
        this->tagName = this->ROOT;
        //lib.writetextfile("log.log", "");
    }
    if (s.length()) {
        s = _trim(s);
        s = _parseTag(s);
        success = setXmlText(s);
        log.push_back("`" + s + "`");
        if (success) {
            log.push_front("Success");
        } else {
            log.push_front("Fail!");
        }
    } else {
        success = false;
        log.push_front("Fail");
    }
    log << "\n====================EOF====================\n";
    //lib.writetextfile("log.log", log.join("\n"), true);
}
/**
 * Заполнить поля tagName attributes
*/
QList<CXml*> CXml::getElementsByTagName(QString tagName) {
    QList<CXml*> list;
    tagName = tagName.toUpper();
    for (int i = 0; i < childs.length(); i++) {
        if (childs[i]->tagName.toUpper() == tagName) {
            list.append(childs[i]);
        }
    }
    return list;
}
/**
 * Заполнить поля tagName attributes
*/
QString CXml::_parseTag(QString s) {
    if (this->tagName != this->ROOT) {
        log << "_parseTag get `" + s + "`";
        QString tagName = "";
        bool detected = false;
        int L = s.length();
        for (int i = 0; i < L; i++) {
            //set tagName
            QChar ch = s[i];
            if (!detected && ch != ' ' && ch != '\n' && ch != '\t' && ch != '<' && ch != '>') {
                tagName += ch;
            } else if (i > 0) {
                detected = true;
                this->tagName = tagName;
                break;
            }
        }
        QString parentTagName = "0";
        if (parentNode) {
            parentTagName = parentNode->tagName;
        }
        log << "I '" + tagName + "', my parent '" + parentTagName + "'";
        int start = _indexOf(s, '>', 0);
        int end   = _lastIndexOf(s, '<', L - 1);
        _parseAttributes(s, tagName, start);
        //TODO check это должно возвращать контент между внешними тегами
        if (this->_isSingleTag) {
            return "";
        }
        log << "will return content middle " + QString::number(start) + " and " + QString::number(end);
        this->innerXML = s.mid(start + 1, end - start - 1);
        return this->innerXML;
    } else {
        return s;
    }
}
/**
 * Тут прежде всего проверяем xml на валидность
 * Заодно собираем теги верхнего уровня в childs
*/
bool CXml::setXmlText(QString xml) {
    xml = _trim(xml);
    //log.clear();
    bool tagLeftIsOpen = false;
    bool tagRightIsOpen = false;
    bool inTagBody = false;     //true когда внутри <t></t>
    bool inTagDefine = false;    //true когда внутри <t> или внутри </t>
    bool quoteIsOpen = false;
    int level = 0;
    int currentLine = 0;
    int currentSymbol = 0;
    QChar lastOpenQuote;

    QString rawTag = "";
    bool started = false; //true если хоть один тег был открыт

    int L = xml.length();
    QString currentTagName = "";
    QString def = "/"; //12.12.2015.2015-12.12 12:37:61";
    bool currentNameIsComplete = false;

    for (int i = 0; i < L; i++) {
        QChar ch = xml[i];
        if (started) {
            rawTag += ch;
        }
        if (ch == '\n') {
            currentLine++;
            currentSymbol = 0;
        }

        if ( inTagDefine && (ch == '\'' || ch == '"')) {
            if (!quoteIsOpen) {
                quoteIsOpen = true;
                lastOpenQuote = ch;
            } else {
                if (lastOpenQuote == ch ) {
                    quoteIsOpen = false;
                    lastOpenQuote = QChar(0);
                }
            }
        }

        if (!quoteIsOpen && ch == '<') {
            if (tagLeftIsOpen || tagRightIsOpen) {
                log.push_back("Invalid symbol '<' at line " + QString::number(currentLine) + ", symbol " + QString::number(currentSymbol));
                return false;
            }
            inTagDefine = true;
            if (i + 1 < L && xml[i + 1] == '/') {
                tagRightIsOpen = true;
            } else {
                tagLeftIsOpen = true;
                if (currentTagName.length() > 0) {
                    currentTagName += def;
                }
                if (!started) {
                    rawTag += ch;
                }
                started = true;
            }
        }
        if (inTagDefine && tagLeftIsOpen) {
            if (!quoteIsOpen && !currentNameIsComplete && ch != '<' && ch != '>') {
                if (isNotPipe(ch)) {
                    currentTagName += ch;
                } else {
                    currentNameIsComplete = true;
                }
            }
        }
        if (!quoteIsOpen && ch == '>') {

            inTagDefine = false;
            if (tagLeftIsOpen) {
                tagLeftIsOpen = false;
                currentNameIsComplete = false; //чтобы можно было добавить разделитель
                level++;
            }
            if (tagRightIsOpen) {
                tagRightIsOpen = false;
                QString closeTagName = _getCloseTagName(xml, i);

                //log << "currentTagName = '" + currentTagName + "',  closeTag = '" + closeTagName + "', level = " + QString::number(level);
                QString openTagName  = _getOpenTagName(currentTagName, def);
                //_closeCurrentTag удаляет крайний справа def + openTagName
                currentTagName = _closeCurrentTag(currentTagName, closeTagName, def, level);
                //log << "after close tag level = " + QString::number(level) + " currentTagName = '" + currentTagName + "'";
                if (level == 0) {
                    log.push_back("will append tag with content " + rawTag);
                    childs.append(new CXml(rawTag, this));
                    rawTag = "";
                }
            }
        }

        currentSymbol++;
    }

    if (level < 0) {
        log.push_back("Invalid xml: quantity open tags not equal quantity close tags");
        return false;
    }
    if (level > 0 && currentTagName.length()) {
        log << "grab no pair tags... '" + currentTagName + "'";
        xml = _grabNoPairTags(xml, def, currentTagName);
        if (rDebug == 0) {
            rDebug++;
            return setXmlText(xml);
        }
        return false;
    }
    if (quoteIsOpen) {
        log.push_back("Invalid xml: You have not closed quote " + QString(lastOpenQuote) + " in xml");
        return false;
    }

    return true;
}
//TODO need test  и надо что-то придумать с   < > внутри тегов (например пишет человек про математику)
/** _trim(xml); удалить все \s символы после <  и перед > */
QString CXml::_trim(QString s) {
    s = s.replace(QRegExp("<\\s*"), "<");
    s = s.replace(QRegExp("\\s*>"), ">");
    return s.trimmed();
}
/** */
QString CXml::_getCloseTagName(QString xml, int pos) {
    QStringList ls;
    int L = xml.length();
    for (int i = pos - 1; i > -1; i--) {
        if (i < 0 || i > L - 1) {
            log.push_back("Out of range!");
        }
        if (xml[i] == '/') {
            break;
        }
        ls.push_front(QString(xml[i]));
    }
    return ls.join("");
}
/** */
QString CXml::_getOpenTagName(QString currentTagName, QString def) {
    if (currentTagName.indexOf(def) == -1) {
        return currentTagName;
    }
    QStringList ls = currentTagName.split(def);
    QString s = ls[ls.length() - 1];
    if (!s.trimmed().length() && (ls.length() - 2) > 0) {
        s = ls[ls.length() - 2];
    }
    return s;
}
/** _closeCurrentTag удаляет крайний справа def + openTagName */
QString CXml::_closeCurrentTag(QString currentTagName, QString closeTagName, QString def, int &level) {
    //log << "remove '/" + closeTagName + "' from '" + currentTagName + "'";
    QStringList ls = currentTagName.split(def);
    int sz = ls.length() - 1;
    int limit = sz;
    while (sz >= 0) {
        if (sz < 0) {
            break;
        }
        QString q = ls[sz];
        if (q.trimmed() != closeTagName) {
            limit--;
            level--;
        } else {
            level--;
            break;
        }
        sz--;
    }
    QStringList result;
    for (int i = 0; i < limit; i++) {
        result.push_back(ls[i]);
    }
    return result.join(def);
    /*QString pattern = "\/" + openTagName + "$";
    QRegExp re (pattern);
    return currentTagName.replace(re, "");*/
}

bool CXml::isNotPipe(QChar ch) {
    if (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t') {
        return false;
    }
    return true;
}
/**
 * Вырезает одинарные теги перечисленные в tags на 0-ом уровне
 * @param QString xml исходный xml
 * @param QString def разделитель имен тегов в tags
 * @param QString цепочка незакрытых тегов, разделенных def
*/
QString CXml::_grabNoPairTags(QString xml, QString def, QString tags) {
    //log << "===============================================";
    xml = _trim(xml);
    bool quoteIsOpen = false;
    bool leftTagIsOpen = false;
    bool rightTagIsOpen = false;
    int currentLine = 0;
    int currentSymbol = 0;
    int level = 0;
    QChar lastOpenQuote;
    int L = xml.length();
    int cutTagStart, cutTagEnd;
    QList <int> limits;
    QString currentTagName = "";

    QStringList tagNames = tags.split(def);
    int i = 0;
    //for (int i = 0; i < tagNames.length(); i++) {
        QString targetTagName = tagNames[i];
        for (int j = 0; j < L; j++) {
            QChar ch = xml[j];
            if (!quoteIsOpen && (ch == '"' || ch == '\'')) {
                quoteIsOpen = true;
                lastOpenQuote = ch;
            }
            if (quoteIsOpen && ch == lastOpenQuote) {
                quoteIsOpen = false;
                lastOpenQuote = QChar(0);
            }


            if(ch == '<' && !quoteIsOpen) {
                if (j + 1 < L && xml[j + 1] != '/') {
                    leftTagIsOpen = true;
                    QString openTagName = _extractOpenTagName(xml, j + 1);
                    if (level == 0 && openTagName == targetTagName) {
                        cutTagStart = j;
                        cutTagEnd = _indexOf(xml, '>', j);
                        log << "will append " + xml.mid(cutTagStart, cutTagEnd - cutTagStart + 1);
                        childs.append(new CXml( xml.mid(cutTagStart, cutTagEnd - cutTagStart + 1), this, true ));
                        limits.append(cutTagStart);
                        limits.append(cutTagEnd + 1); //для последующего удаления при проходе по этому массиву
                        level--; //при инкременте открытых левых тегов все придет в норму
                        //log << "decrement level, because it nopair tag, after decrement level = " + QString::number(level);
                        if (i + 1 < tagNames.length()) {
                            i++;
                            targetTagName = tagNames[i];
                        } else {
                            targetTagName = "NoEXISTS_TAG_2016-08-21-3-25";
                        }
                    }
                    if (!currentTagName.length()) {
                        currentTagName = openTagName;
                    } else {
                        currentTagName += def + openTagName;
                    }
                }
                if (j + 1 < L && xml[j + 1] == '/') {
                    rightTagIsOpen = true;
                    QString closeTagName = _extractOpenTagName(xml, j + 2);
                    currentTagName = _closeCurrentTag(currentTagName, closeTagName, def, level);
                    //log <<  "_closeCurrentTag on currentTagName = '" + currentTagName +  "' and close tag '" + closeTagName + "'', after decrement level = " + QString::number(level);
                }
            }
            if(ch == '>' && !quoteIsOpen && leftTagIsOpen) {
                level++;
                //log << "increment level, because it close left tag, after increment level = " + QString::number(level);
                leftTagIsOpen = false;
                rightTagIsOpen = false;
            }

        }
    //}//end tagNames cycle
    QString newXml = "";
    for (i = 0; i < L; i++) {
        bool append = true;
        for (int j = 0; j < limits.length(); j += 2) {
            int min = limits[j];
            int max = min;
            if (j + 1 < limits.length()) {
                max = limits[j + 1];
            }
            if (i >= min && i <= max) {
                append = false;
                break;
            }
        }
        if (append) {
            newXml += xml[i];
        }
    }
    //log << "\nafter cut return\n\n";
    //log << newXml;
    //log << "~~~~~~~~~~~~~~~~~~~~~~";
    return newXml;
}
/**
 * QString xml
 * int pos
*/
QString CXml::_extractOpenTagName(QString xml, int pos) {
    QString r = "";
    int L = xml.length();
    if (pos > L - 1) {
        pos = L - 1;
    }
    if (pos < 0) {
        pos = 0;
    }
    for (int i = pos; i < L; i++) {
        QChar ch = xml[i];
        if (ch != ' ' && ch != '>' && ch != '\n' && ch != '\t') {
            r += ch;
        } else {
            break;
        }
    }
    return r;
}

/**
 * QString xml
 * QChar ch
 * int pos
*/
int CXml::_indexOf(QString xml, QChar needle, int pos) {
    int L = xml.length();
    if (pos > L - 1) {
        pos = L - 1;
    }
    if (pos < 0) {
        pos = 0;
    }
    bool inQuote = false;
    QChar lastQuote;
    for (int i = pos; i < L; i++) {
        QChar ch = xml[i];
        if (!inQuote && (ch == '"' || ch == '\'') ) {
            lastQuote = ch;
            inQuote = true;
        }
        if (inQuote && ch == lastQuote) {
            lastQuote = QChar(0);
            inQuote = false;
        }
        if (!inQuote && ch == needle) {
            return i;
        }
    }
    return -1;
}

/**
 * QString xml
 * QChar ch
 * int pos
*/
int CXml::_lastIndexOf(QString xml, QChar needle, int pos) {
    int L = xml.length();
    if (pos > L - 1) {
        pos = L - 1;
    }
    if (pos < 0) {
        pos = 0;
    }
    bool inQuote = false;
    QChar lastQuote;
    for (int i = pos; i > -1; i--) {
        QChar ch = xml[i];
        if (!inQuote && (ch == '"' || ch == '\'') ) {
            lastQuote = ch;
            inQuote = true;
        }
        if (inQuote && ch == lastQuote) {
            lastQuote = QChar(0);
            inQuote = false;
        }
        if (!inQuote && ch == needle) {
            return i;
        }
    }
    return -1;
}
/**
 * анализ атрибутов DOM узла
 * @param QString xml
 * @param  QString tagName
 * @param int length
*/
void CXml::_parseAttributes(QString xml, QString tagName, int length) {
    xml = xml.mid(0, length);
    xml = xml.replace("<" + tagName, "");
    bool quoteIsOpen = false;
    QChar ch, lastQuote;
    bool valueStarted = false;
    bool valueExpected = false;
    bool nameIsBreak = false;
    QString abet = "abcdefghijklmnopqrstuvwxyz";
    abet += abet.toUpper();

    QString name = "";
    QString value = "";

    for (int i = 0; i < xml.length(); i++) {
        ch = xml[i];
        if (!quoteIsOpen && (ch == '"' || ch == '\'') ) {
            lastQuote = ch;
            quoteIsOpen = true;
            continue;
        }
        if (quoteIsOpen && ch == lastQuote) {
            if (value.length() && name.length()) {
                attributes->addAttribute(name, value);
                value = name = "";
            }
            lastQuote = QChar(0);
            quoteIsOpen = false;
            valueExpected = false;
        }

        if (!quoteIsOpen) {
            if (abet.indexOf(ch) != -1) {
                if (nameIsBreak) {
                    attributes->addAttribute(name);
                    name = "";
                    nameIsBreak = false;
                }
                name += ch;
            } else if (name.length()) {
                nameIsBreak = true;
            }
            if (ch == '=') {
                valueExpected = true;
            }
        } else {
            if (valueExpected) {
                value += ch;
            }
        }
    }

}
QString CXml::getAttribute(QString title) {
    return this->attributes->getByName(title);
}
