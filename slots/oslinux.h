#ifndef OSLINUX_H
#define OSLINUX_H

#include <QObject>

#include <QWidget>
#include <QProcess>
#include <QString>
#include <QByteArray>
#include <QFile>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QRegExp>
#include <QList>
#include <QWebFrame>
#include <string>

#include "../lib/utils.h"
#include "../logic/process/cprocess.h"
#include "../ui/cwebview.h"


class OSLinux : public QObject
{
    Q_OBJECT
public:
    explicit OSLinux(QObject *parent = 0, CWebView *webView = 0);
    QString getLocalFileStartUrl();
signals:
    
public slots:
    int ShellExecute(QString operation, QString path, QString params, QString directory, bool showCmdLine = false);
    void onCProcessFinish(QString evaluateJavaScript, unsigned int resId);

private:
    CWebView *webView;
    CProcess * _cproc;
    QList<CProcess *> cprocList;
    unsigned int cprocId;
    
};

#endif // OSLINUX_H
