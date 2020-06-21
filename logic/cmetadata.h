#ifndef CMETADATA_H
#define CMETADATA_H

#include <QString>
#include <QStringList>
#include <QFile>
#include "../lib/utils.h"

class CMetadata
{
public:
    CMetadata(QString file = "", int argc = 0, char** argv = 0);
    QString sTitle;
    /** window buttons */
    bool min = true;
    bool max = true;
    bool close = true;
    bool question = false;

    /** win style*/
    bool onlyTop = false;
    bool noFrame = false;
    bool fullScreen = false;

    /** win size */
    int windowHeight;
    int windowWidth;
    bool fixedSize;

    static QString PIPE;

    QStringList getArgs();

    //TODO главное меню окна

private:
    QString _sHead;
    QString _sMenu;
    QString _getHead();
    Utils lib;
    QStringList args;

    void _setTitle(QStringList aTitle);
    void _setWinButtons(QStringList aMeta);
    int _parseNumAttr(int pos, QString s);
    void _initArgv(int argc, char** argv);

};

#endif // CMETADATA_H
