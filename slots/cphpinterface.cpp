#include "cphpinterface.h"

CPhpInterface::CPhpInterface(QWidget *parent, CWebView *webView) :
    QWidget(parent)
{
    procIsInit = false;
    this->webView = webView;
    cprocId = 0;
}

int CPhpInterface::file_put_contents(QString path, QString data, int flag) {
    bool append = flag == 1;
    return lib.writetextfile(path, data, append);
}

bool CPhpInterface::file_exists(QString path) {
    return QFile::exists(path);
}

bool CPhpInterface::is_dir(QString path) {
    QFileInfo info;
    info.setFile(path);
    return info.isDir();
}

qint64  CPhpInterface::filesize(QString path) {
    Utils lib;
    if (this->is_dir(path)) {
        QString folders = this->_scandir(path);
        QStringList ls = folders.split(CMetadata::PIPE);
        qint64 sz = 0;
        for (int i = 0; i < ls.size(); i++) {
            QString currPath = ls[i];
            QString shortname = ls[i].replace(path + "/", "");
            if (shortname != "." && shortname != "..") {
                sz += this->filesize(currPath);
            }
        }
        return sz;
    }
    QFileInfo info;
    info.setFile(path);
    return info.size();
}

QString CPhpInterface::_scandir(QString path) {
    QDirIterator it(path, QDirIterator::NoIteratorFlags);
    QStringList ls;
    while (it.hasNext()) {
        ls.append(it.next() );
    }
    return ls.join(CMetadata::PIPE);
}


QString CPhpInterface::file_get_contents(QString path) {
    return lib.readtextfile(path, true);
}
unsigned int CPhpInterface::exec(QString command, QString onFinish, QString onOutput, QString onError) {
    return this->execCProcess(command, onFinish, onOutput, onError);
}

unsigned int CPhpInterface::execCProcess(QString command, QString onFinish, QString onOutput, QString onError) {
    cprocId++;
    CProcess * proc = new CProcess(cprocId, onOutput, onError, onFinish, this);
    connect(proc, SIGNAL(onOutputSg(QString, unsigned int)),
                  this, SLOT(onCProcessOutput(QString , unsigned int )));
    connect(proc,
            SIGNAL(
                onErrorSg(QString, unsigned int)),
            this, SLOT(
                onCProcessErrorOutput(QString, unsigned int))
           );
    connect(proc, SIGNAL(onEmptyArgumentsSg()),
            this, SLOT(onCProcessEmptyArguments()));

    connect(proc, SIGNAL(onEmptyOutputSg(bool)),
            this, SLOT(onCProcessEmptyOutput(bool)) );

    connect(proc, SIGNAL(onFinishSg(QString, unsigned int)),
            this, SLOT(onCProcessFinish(QString, unsigned int)) );

    proc->exec(command);
    cprocList.append(proc);
    return cprocId;
}

void CPhpInterface::onCProcessOutput(QString evaluateJavaScript, unsigned int resId) {
    //lib.qMessageBox("CPhp", "onCProcessOutput!");
        this->webView->page()
                ->currentFrame()
                ->evaluateJavaScript(evaluateJavaScript);
}

void CPhpInterface::onCProcessErrorOutput(QString onErrorOutputEvaluateJavaScript, unsigned int resId) {
    //lib.qMessageBox("CPhp", "onCProcessERROutput!");
    this->webView->page()
                ->currentFrame()
                ->evaluateJavaScript(onErrorOutputEvaluateJavaScript);
}

void CPhpInterface::onCProcessEmptyArguments() {
    this->webView->page()->currentFrame()->evaluateJavaScript("alert('OnEmptyArgs')");
}

void CPhpInterface::onCProcessEmptyOutput(bool isErrorOutput) {
    QString s = "alert('OnEmptyOut')";
    if (isErrorOutput) {
        s = "alert('OnEmptyErrOut')";
    }
    this->webView->page()->currentFrame()->evaluateJavaScript(s);
}
void CPhpInterface::onCProcessFinish(QString evaluateJavaScript, unsigned int resId) {
    //lib.qMessageBox("CPhp", "onCProcessFinish(" + evaluateJavaScript + ")");
    this->webView->page()->currentFrame()->evaluateJavaScript(evaluateJavaScript);
}
bool CPhpInterface::isRun(unsigned int n) {
    for (unsigned int i = 0; i < cprocList.length(); i++)  {
        if (cprocList[i]->id() == n) {
            return cprocList[i]->isRun();
        }
    }
    return false;
}
unsigned int CPhpInterface::getSysId(unsigned int n) {
    for (unsigned int i = 0; i < cprocList.length(); i++)  {
        if (cprocList[i]->id() == n) {
            return cprocList[i]->systemId();
        }
    }
    return 0;
}

bool CPhpInterface::unlink(QString path) {
    if (this->file_exists(path)){
        return QFile::remove(path);
    }
    return true;
}
