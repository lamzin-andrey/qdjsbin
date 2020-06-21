#include "cmetadata.h"

QString CMetadata::PIPE = "_;__PIPE__;_";

CMetadata::CMetadata(QString file, int argc, char** argv)
{
    this->_initArgv(argc, argv);
    file = file + "/index.html";
    QString s = lib.readtextfile(file, true);
    QStringList arr = s.split('\n');

    QStringList aHead;
    int headComplete = 0;

    QStringList aMenu;
    int menuComplete = 0;

    QStringList aTitle;
    int titleComplete = 0;

    QStringList aMeta;

    windowWidth = -1;
    windowHeight = -1;
    fixedSize = false;

    for (int i = 0; i < arr.length(); i++) {
        s = arr[i];
        if (s.indexOf("<head") != -1) {
            headComplete = 1;
        }
        if (headComplete == 1) {
            aHead.append(arr[i]);
        }
        if (s.indexOf("</head>") != -1) {
            headComplete = 2;
        }

        if (s.indexOf("<menu") != -1) {
            menuComplete = 1;
        }
        if (menuComplete == 1) {
            aMenu.append(arr[i]);
        }
        if (s.indexOf("</menu>") != -1) {
            menuComplete = 2;
            break;
        }

        if (s.indexOf("<title") != -1) {
            titleComplete = 1;
        }
        if (titleComplete == 1) {
            aTitle.append(arr[i]);
        }
        if (s.indexOf("</title>") != -1) {
            titleComplete = 2;
        }

        if (s.indexOf("<meta") != -1) {
            aMeta.append(arr[i]);
        }
    }
    _setTitle(aTitle);
    _setWinButtons(aMeta);
}

void CMetadata::_setWinButtons(QStringList aMeta) {
    for (int i = 0; i < aMeta.length(); i++) {
        QString s = aMeta[i];
        QString mark = "windowButtons";
        int n = s.indexOf(mark);
        if (n != -1) {
            mark = "content";
            n = s.indexOf(mark);
            int qq = 0;
            QString mask = "";
            if (n != -1) {
                for (int j = n + mark.length(); j < s.length(); j++) {
                    QChar ch = s[j];
                    if (ch == '"' || ch == '\'') {
                        qq++;
                        continue;
                    }
                    if (qq == 1) {
                        mask += ch;
                    }
                    if (qq == 2) {
                        break;
                    }
                }
                if (qq == 2 && mask.length() == 4) {
                    min      = (mask[0] == '1');
                    max      = (mask[1] == '1');
                    close    = (mask[2] == '1');
                    question = (mask[3] == '1');
                }
            }

            if (s.indexOf("onlyTop") != -1) {
                onlyTop = true;
            }
            if (s.indexOf("noFrame") != -1) {
                noFrame = true;
            }
            if (s.indexOf("fullScreen") != -1) {
                fullScreen = true;
            }

            if (s.indexOf("fixed") != -1) {
                fixedSize = true;
            }

            int widthPos = s.indexOf("width=");
            if (widthPos != -1) {
                windowWidth = _parseNumAttr(widthPos, s);
            }

            int heightPos = s.indexOf("height=");
            if (heightPos != -1) {
                windowHeight = _parseNumAttr(heightPos, s);
            }

            break;
        }
    }
}

void CMetadata::_setTitle(QStringList aTitle) {
    QString s = aTitle.join('\n');
    int st = s.indexOf("<title");
    st = s.indexOf(">", st);
    int end = s.indexOf("</title", st);
    if (st < end && end) {
        s = s.mid(st + 1, end - st - 1);
        sTitle = s.trimmed();
    }
    sTitle = s.trimmed();
}


int CMetadata::_parseNumAttr(int pos, QString s) {
    int start = s.indexOf('"', pos);
    if (start != -1) {
        int end  = s.indexOf('"', start + 1);
        if (end != -1) {
            QString v = s.mid(start + 1, end - start - 1);
            bool ok = false;
            int n = v.toInt(&ok);
            if (ok) {
                return n;
            }
        }
    }
    return -1;
}

void CMetadata::_initArgv(int argc, char** argv) {
    if (argc > 2) {
        for (int i = 2; i < argc; i++) {
            this->args.push_back(QString(argv[i]));
        }
    }
}

QStringList CMetadata::getArgs() {
    return this->args;
}
