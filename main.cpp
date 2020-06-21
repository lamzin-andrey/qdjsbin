#include "ui/cwindow.h"
#include "logic/cmetadata.h"
#include <QApplication>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString path = QApplication::applicationDirPath() + "/default";
    if (argc > 1) {
        path = QString(argv[1]);
    }
    //TODO class for анализ ваших всяких вещей, типа какие иконки у окна показывать
    CMetadata data(path, argc, argv);
    CWindow w(path, data);
    //w.show();
    
    return a.exec();
}

