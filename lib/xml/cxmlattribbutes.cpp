#include "cxmlattribbutes.h"

CXmlAttribbutes::CXmlAttribbutes()
{
    this->UNDEFINED_VALUE = "CXmlAttibutes_UNDEFINED_VALUE_2016_21-08";
    this->_length = 0;
}

void CXmlAttribbutes::addAttribute(QString name, QString value) {
    this->names.append(name);
    this->values.append(value);
    this->_length++;
}

int CXmlAttribbutes::length() {
    return this->_length;
}

QString CXmlAttribbutes::getByName(QString name) {
    name = name.toUpper();
    for (int i = 0; i < this->names.length(); i++) {
        if (this->names[i].toUpper() == name) {
            QString r = this->values[i];
            if (r == this->UNDEFINED_VALUE) {
                return "";
            }
            return r;
        }
    }
    return "";
}
