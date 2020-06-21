#include "caction.h"

CAction::CAction(QString text, QString jsAction) :    QObject() {
    this->_text = text;
    this->_jsAction = jsAction;
}

void CAction::triggered() {
    emit(triggeredExt(this->_text, this->_jsAction));
}

