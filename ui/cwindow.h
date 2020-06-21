#ifndef CLOADERDLG_H
#define CLOADERDLG_H

#include <QMainWindow>
#include <QtGui>
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include <QUrl>
#include <QHBoxLayout>
#include "cwebview.h"
#include <QtWebKitWidgets/QWebFrame>
#include <QTimer>
#include <QScreen>
#include <QDesktopWidget>
#include <QImage>
#include <QByteArray>
#include <QTextStream>
#include "../lib/utils.h"
#include "../lib/binfile.h"
#include "../slots/cphpinterface.h"
#include "../slots/os.h"
#include "../logic/cmetadata.h"
#include "caction.h"
#include "../lib/xml/cxml.h"
#include "../lib/json/cjson.h"


class CMetadata;

class CWindow : public QMainWindow
{
    Q_OBJECT
public:
    CWindow(QString appDir, CMetadata metadata, QWidget *parent = 0);
    ~CWindow();
    void loadImages(bool flag);
    void stop();
    void getURL(QString url, bool writeresult = true);
    void fixSize();
    void setHtml(QString s);
    void js(QString script);
    QString currentHtml();
    QString currentText();
    void addObject(QObject* object, QString jsName);

    QString html;
 private:
    QMenuBar *menubar;
    CWebView * wv;
    bool loading;
    QString lastUrl;
    unsigned int counttry;
    Utils lib;
    bool writeresult;
    QString workdir;    //folder runned app
    CPhpInterface *php; //Widget реализующий php like интерфейс для работы с файлами (возможно в будущем не только)
    OS *os; //Widget реализующий специфичные для OS API функции, такие как ShellExecute
    CMetadata metadata;
    CXml* cXml;

    QTimer *timer;      //переменные изменения размера окна
    bool resized;

    //главное меню окна
    void _setMainMenu();
    void _setMenuItems(QMenu* menu, QList<CXml*> items);
    QString _transliteApp(QString key);
    CJSON* _localeJSON;
    void _initLocale();
    void _saveImageFromByteArray(QByteArray ba, QString path, QString ext, int quality);
 private slots:
    void onLoad(bool success);
    void onMainMenuAction(QString title, QString action);

 public slots:
    QString appDir();
    QString getLineDelimeter();
    void setLineDelimeter(QString  pipe);
    void onTimer(QPrivateSignal);
    void quit();
    void moveTo(int x, int y);
    void resizeTo(int x, int y);
    void maximize();
    void minimize();
    QString openFileDialog(QString caption, QString dir, QString filter);
    QString saveFileDialog(QString caption, QString dir, QString filter);
    QString openDirectoryDialog(QString caption, QString dir);
    int getLastKeyCode();
    QString getLastKeyChar();
    QStringList getArgs();
    void hideMainMenu();
    void showMainMenu();
    void setTitle(QString s);
    void savePng(QString path, QString base64Data, int quality);
    void saveJpeg(QString path, QString base64Data, int quality);
    QString readFileAsBinaryString(QString filename, long offset = 0, long limit = -1);
    void copyFile(QString src, QString dest, long srcOffset = 0, long srcLimit = -1);

 signals:
    void loadComplete();
    void errorConnect(QString msg);
};

#endif // CLOADERDLG_H

