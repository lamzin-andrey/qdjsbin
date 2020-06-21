#ifndef UTILS_H
#define UTILS_H
//#define AR_SIZE = 64000

#include <QMessageBox>
#include <QString>
#include <string>
#include <iostream>
#include <QMainWindow>
#include <QRegExp>
#include <math.h>
#include <QFile>
#include <QApplication>
#include <QDir>
#include "utilsstd.h"
using namespace std;

class Utils
 {
public:
        Utils();
        QWidget *parentMBoxWidget;
        bool buttonRus;
        QString cyr;
        QString lat;
        bool convertCyr;
        void recursiveDrop(QString filename);
        QString qMessageBox(QString caption, QString text, QString type = "error", QString fb = "", QString sb = "", QString tb = "");
	int pos(QString substr, string s);
	int pos(string substr, QString s);
	int pos(QString substr, QString s);
	int pos(char sim, QString s);
	QString qstring(string s);
	int getQuantitySubstr(QString substr, QString str);
	int getPosSubstrN(QString substr, QString str, int number);
	int nextSubstrPos(QString substr, QString src, QString &ctrlstr);
	//QString qRusstring(string s);
	string stdstring(QString qs);
	QString intToStr(int x);
	QString expToDec(QString s);
	QString Delete(string s, int pos, int count);
	QString Delete(QString s, int pos, int count);
	int qStringToChar(QString s);
	QString rus(QString rustext);
	QString fromUtf8(QString rusTextFromDBMySQL);
	QString toUtf8(QString text);
	void replaceAll(QString &str, QChar src, QChar _new);
	void getScreenSize(QDialog * wnd, int &w, int &h);
	void getScreenSize(QMainWindow * wnd, int &w, int &h);
    QString readtextfile(QString fileName, bool silent = false);
    int writetextfile(QString fileName, QString data, bool append = false);
    int hexStrToDec(QString hexPair);
    int hexChar2Int(QChar ch);
     void log(QString text);
	//fields
	char * data;
	int size;
private:
	string rToStr(int n);
 };
void trim(QString &str, QChar sim);
#endif //
