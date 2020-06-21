#include "oslinux.h"

OSLinux::OSLinux(QObject *parent, CWebView *webView): QObject(parent)
{
    //procIsInit = false;
    this->webView = webView;
    cprocId = 0;
}


int OSLinux::ShellExecute(QString operation, QString path, QString params, QString directory, bool showCmdLine) {
    cprocId++;
    QString a = "", b = "", c = "QT_ON_FINISH";
    CProcess * proc = new CProcess(cprocId, a, b, c);
    connect(proc, SIGNAL(onFinishSg(QString, unsigned int)),
            this, SLOT(onCProcessFinish(QString, unsigned int)) );
    QString command = path + " " + params;
    proc->exec(command, directory);
    cprocList.append(proc);
    return 0;
}

void OSLinux::onCProcessFinish(QString evaluateJavaScript, unsigned int resId) {
    //lib.qMessageBox("CPhp", "onCProcessFinish(" + evaluateJavaScript + ")");
    this->webView->page()->currentFrame()->evaluateJavaScript(evaluateJavaScript);
}


QString OSLinux:: getLocalFileStartUrl() {
    return "file://localhost";
}

