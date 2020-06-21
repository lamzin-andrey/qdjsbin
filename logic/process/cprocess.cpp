#include "cprocess.h"

CProcess::CProcess(unsigned int resId, QString onOutput, QString onError, QString onFinish, QWidget *parent) :   QWidget(parent){
    this->_resId = resId;
    this->_onOutput = onOutput;
    this->_onError  = onError;
    this->_onFinish = onFinish;
    this->_procIsInit = false;
}

void CProcess::exec(QString command, QString workDir) {
    QString execPath = _parseCommand(command);
    if (execPath.trimmed() == "") {
        //this->webView->page()->currentFrame()->evaluateJavaScript("alert('OnEmptyARg')");
        emit(onEmptyArgumentsSg());
        return;
    }
    if (_procIsInit) {
        _proc->close();
    } else {
        _proc = new QProcess;
        _proc->setReadChannel(QProcess::StandardOutput);
        if (workDir.length()) {
            _proc->setWorkingDirectory(workDir);
        }

        //proc->setReadChannel(QProcess::StandardError);
        _proc->setEnvironment(QProcess::systemEnvironment());
        connect( _proc, SIGNAL(readyReadStandardOutput()), this, SLOT(onOutput()) );
        connect( _proc, SIGNAL(readyReadStandardError()), this, SLOT(onErrorOutput()) );
        connect( _proc, SIGNAL(finished(int)), this, SLOT(onFinish()) );
        _procIsInit = true;
    }
    //lib.qMessageBox("CProcess", "start " + execPath + " with args: (" + _execArgs.join(',') + ")");
    _proc->start(execPath, _execArgs);
    _sysId = (unsigned int) _proc->pid();
}

QString CProcess::_parseCommand(QString command) {
    QRegExp re("\\s");
    QStringList ls = command.split(re);
    _execArgs.clear();
    QString result = ls[0].trimmed();
    for (int i = 1; i < ls.size(); i++) {
        _execArgs.append(ls[i].trimmed());
    }
    return result;
}

void CProcess::onOutput() {
    //lib.qMessageBox("CProcess", "onO");
        if ( !_proc->isReadable() ) {
            //lib.qMessageBox("CProcess", "onO - b emit onEmptyOutputSg");
            //this->webView->page()->currentFrame()->evaluateJavaScript("alert('empty output');");
            emit(onEmptyOutputSg(false));
            return;
        }
        QByteArray *ba = new QByteArray();
        *ba = _proc->readAllStandardOutput();

        QString s = QString::fromUtf8(ba->data()).replace('\n', "\\n");
        s = s.replace('\'', "\\'");
        s = s.replace('"', "\\\"");
        //lib.qMessageBox("CProcess", "onO - b emit onOutputSg(" + _onOutput + "('" + s + "');" + ")");

        if (_onOutput.length()) {
            emit(onOutputSg(_onOutput + "('" + s + "');", _resId));
        }
        this->_output.append(s);
}

void CProcess::onErrorOutput() {
    //lib.qMessageBox("CProcess", "onEO");
        if ( !_proc->isReadable() ) {
            //lib.qMessageBox("CProcess", "onEO - b emit onEmptyOutputSg");
            //this->webView->page()->currentFrame()->evaluateJavaScript("alert('Unable read error stream');");
            emit(onEmptyOutputSg(true));
            return;
        }
        QByteArray *ba = new QByteArray();
        *ba = _proc->readAllStandardError();
        QString s = QString(ba->data()).replace('\n', "\\n");
        s = s.replace('\'', "\\'");
        s = s.replace('"', "\\\"");
        //this->webView->page()->currentFrame()->evaluateJavaScript(jsOnErrorOutput + "('" +  s + "');");
        //lib.qMessageBox("CProcess", "onEO - b emit onOutputSg(" + _onOutput + "('" + s + "');" + ")");
        if (_onError.length()) {
            emit(onErrorSg(_onError + "('" + s + "');", _resId));
        }
        this->_errors.append(s);
}

void CProcess::onFinish() {
    //lib.qMessageBox("CProcess", "onFin");
    QString o = _output.join(CMetadata::PIPE);
    QString e = _errors.join(CMetadata::PIPE);
    emit(onFinishSg("QtBrige.onFinish('" + _onFinish + "', '" +  o  + "', '" + e + "');", _resId));
}
bool CProcess::isRun() {
    if (_proc->state() == QProcess::NotRunning) {
        return false;
    }
    return true;
}
unsigned int CProcess::id() {
    return _resId;
}
/**
 * @description Возвращает id системного процесса
*/
unsigned int CProcess::systemId() {
    return _sysId;
}
