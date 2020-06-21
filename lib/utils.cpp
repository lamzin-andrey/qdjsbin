#include "utils.h"

Utils:: Utils() {
    parentMBoxWidget = 0;
    cyr = "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    lat = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    buttonRus = convertCyr = true;
};


void Utils::recursiveDrop(QString filename)
{
    QDir dir;
    if (dir.cd(filename))
    {
        //this->qMessageBox("Ulib", "current dirName  \n" + filename);
        QStringList dirlist = dir.entryList(QDir::Dirs);
        for (int i = 0; i < dirlist.size(); i++)
        {
            //this->qMessageBox("Ulib", "recursive for   \n" + filename + "/" + dirlist[i]);
            if ((dirlist[i] != ".")&&(dirlist[i] != ".."))
                recursiveDrop(filename + "/" + dirlist[i]);
        }
        QStringList filelist = dir.entryList(QDir::Files);
        for (int i = 0; i < filelist.size(); i++)
        {
           // this->qMessageBox("Ulib", "delete file   \n" + filename + "/" + filelist[i]);
            QFile::remove(filename + "/" + filelist[i]);
        }
        //this->qMessageBox("Ulib", "try drop   \n" + filename);
        dir.rmdir(filename);
    }
}

QString Utils::qMessageBox(QString caption, QString text, QString type, QString fb, QString sb , QString tb )
{
        if (convertCyr) text = rus(text);
        if (convertCyr) caption = rus(caption);
        long int iType = 0;
	if ((type == "Information")||(type == "information")) iType = QMessageBox::Information;	
	if ((type == "Warning")||(type == "warning")) iType = QMessageBox::Warning;
	if ((type == "Error")||(type == "error")||(type == "Critical")||(type == "critical")) iType = QMessageBox::Critical;
	if ((type =="Question")||(type == "question")) iType = QMessageBox::Question;
	
        long int iFb = 0;
	if ((fb == "Yes")||(fb == "yes")) iFb = QMessageBox::Yes;	
	if ((fb == "No")||(fb == "no")) iFb = QMessageBox::No;
	if ((fb == "Cancel")||(fb == "cancel")) iFb = QMessageBox::Cancel;
	
        long int iSb = 0;
	if ((sb == "Yes")||(sb == "yes")) iSb = QMessageBox::Yes;	
	if ((sb == "No")||(sb == "no")) iSb = QMessageBox::No;
	if ((sb == "Cancel")||(sb == "cancel")) iSb = QMessageBox::Cancel;
	
        long int iTb = 0;
	if ((tb == "Yes")||(tb == "yes")) iTb = QMessageBox::Yes;	
	if ((tb == "No")||(tb == "no")) iTb = QMessageBox::No;
	if ((tb == "Cancel")||(tb == "cancel")) iTb = QMessageBox::Cancel;
	
        QMessageBox *mb = new QMessageBox
	(
	caption, 
	text, 
	(QMessageBox::Icon) iType, 
	iFb,
	iSb,
        iTb,
        parentMBoxWidget);

        if (buttonRus) {
            mb->setButtonText(QMessageBox::Yes, rus("Да"));
            mb->setButtonText(QMessageBox::No, rus("Нет"));
            mb->setButtonText(QMessageBox::Cancel, rus("Отмена"));
        }

	int n = mb->exec();
	delete mb;
	QString result = "";
	switch (n)
	{
		case QMessageBox::Yes:
			result = "yes";
			break;
		
		case QMessageBox::No:
			result = "no";
			break;
			
		case QMessageBox::Cancel:
			result = "cancel";
			break;
	}
	return result;
}
//--------------------------------------------------------
int Utils::pos(QString substr, string s)
{
	bool f = false;
	int rez = -1;
	for (unsigned int i = 0; i < s.length(); i++)
		if (substr[0] == s[i])
		{
			f = true;
			for (int j = 0; j < substr.length(); j++)
				if (s[i+j] != substr[j]) f = false;
			if (f) {rez = i; break;}
		}
	return rez;	
}
//--------------------------------------------------------
int Utils::pos(string substr, QString s)
{
	bool f = false;
	int rez = -1;
	for (int i = 0; i < s.length(); i++)
		if (substr[0] == s[i])
		{
			f = true;
			for (unsigned int j = 0; j < substr.length(); j++)
				if (s[i+j] != substr[j]) f = false;
			if (f) {rez = i; break;}
		}
	return rez;	
}
//----------------------------------------------------
int Utils::pos(QString substr, QString s)
{
	bool f = false;
	int rez = -1;
	for (int i = 0; i < s.length(); i++)
		if (substr[0] == s[i])
		{
			f = true;
			for (int j = 0; j < substr.length(); j++)
				if (s[i+j] != substr[j]) f = false;
			if (f) {rez = i; break;}
		}
	return rez;	
}
//-----------------------------------------------------
int Utils:: pos(char sim, QString qs)
{
	QChar * data = qs.data();
	int i = 0;
	while (i < qs.length()) 
		{
			char t =  (char)data->unicode(); 
			if (t == sim) return i;
			++data; 
			i++;
		}
	return -1;
}
//-----------------------------------------------------
QString Utils:: qstring(string s)
{
	QString qs;
	for (unsigned int i = 0; i < s.length(); i++) qs += s[i];
	return qs;
}
//-------------------------------------------
/*QString Utils:: qRusstring(string s)
{
	QString qs;
	for (int i = 0; i < s.length(); i++) 
	{
		switch((unsigned int) s[i]){
			case 48: qs += "Р°";
			break;
			case 49: qs += 'Р±';
			break;
			case 50: qs += 'РІ';
			break;
			case 51: qs += 'Рі';
			break;
			case 52: qs += 'Рґ';
			break;
			case 53: qs += 'Рµ';
			break;
			case 81: qs += 'С‘';
			break;
			case 54: qs += 'Р¶';
			break;
			case 55: qs += 'Р·';
			break;
			case 56: qs += 'Рё';
			break;
			case 57: qs += 'Р№';
			break;
			case 58: qs += 'Рє';
			break;
			case 59: qs += 'Р»';
			break;
			case 60: qs += 'Рј';
			break;
			case 61: qs += 'РЅ';
			break;
			case 62: qs += 'Рѕ';
			break;
			case 63: qs += 'Рї';
			break;
			case 64: qs += 'СЂ';
			break;
			case 65: qs += 'СЃ';
			break;
			case 66: qs += 'С‚';
			break;
			case 67: qs += 'Сѓ';
			break;
			case 68: qs += 'С„';
			break;
			case 69: qs += 'С…';
			break;
			case 70: qs += 'С†';
			break;
			case 71: qs += 'С‡';
			break;
			case 72: qs += 'С€';
			break;
			case 73: qs += 'С‰';
			break;
			case 74: qs += 'СЉ';
			break;
			case 75: qs += 'С‹';
			break;
			case 76: qs += 'СЊ';
			break;
			case 77: qs += 'СЌ';
			break;
			case 78: qs += 'СЋ';
			break;
			case 79: qs += 'СЏ';
			break;
			case 16: qs += 'Рђ';
			break;
			case 17: qs += 'Р‘';
			break;
			case 18: qs += 'Р’';
			break;
			case 19: qs += 'Р“';
			break;
			case 20: qs += 'Р”';
			break;
			case 21: qs += 'Р•';
			break;
			case 1: qs += 'РЃ';
			break;
			case 22: qs += 'Р–';
			break;
			case 23: qs += 'Р—';
			break;
			case 24: qs += 'Р';
			break;
			case 25: qs += 'Р™';
			break;
			case 26: qs += 'Рљ';
			break;
			case 27: qs += 'Р›';
			break;
			case 28: qs += 'Рњ';
			break;
			case 29: qs += 'Рќ';
			break;
			case 30: qs += 'Рћ';
			break;
			case 31: qs += 'Рџ';
			break;
			case 32: qs += 'Р ';
			break;
			case 33: qs += 'РЎ';
			break;
			case 34: qs += 'Рў';
			break;
			case 35: qs += 'РЈ';
			break;
			case 36: qs += 'Р¤';
			break;
			case 37: qs += 'РҐ';
			break;
			case 38: qs += 'Р¦';
			break;
			case 39: qs += 'Р§';
			break;
			case 40: qs += 'РЁ';
			break;
			case 41: qs += 'Р©';
			break;
			case 42: qs += 'РЄ';
			break;
			case 43: qs += 'Р«';
			break;
			case 44: qs += 'Р¬';
			break;
			case 45: qs += 'Р­';
			break;
			case 46: qs += 'Р®';
			break;
			case 47: qs += 'РЇ';
			break;			
			default:
			qs += s[i];}
	}
	return qs;
}
*/
//-----------------------------------------------------------------------
QString Utils::intToStr(int x)
{
	QString r = "";
	if (x == 0) return "0";
	if (x < 0) { r = "-"; x *= -1;}
	string inv = "";
	x *= 10;
	while (x != 0)
	{
		int y = (int)floor(x/10);
		int n = x - y*10;
		inv += rToStr(n);
		x = y;
	}
	string p = "";
	for (int i = inv.length() - 1; i > 0; i--)
		p += inv[i];
	cout << p << '\n';
	r += qstring(p);
	QString NaN = "NaN";
	if (pos(NaN, r) > -1 ) r = NaN;
	return r;
}
//------------------------------------------------------------------
string Utils::rToStr(int n)
{
	if (n == 0) return "0";
	if (n == 1) return "1";
	if (n == 2) return "2";
	if (n == 3) return "3";
	if (n == 4) return "4";
	if (n == 5) return "5";
	if (n == 6) return "6";
	if (n == 7) return "7";
	if (n == 8) return "8";
	if (n == 9) return "9";
	return "NaN";
}

//------------------------------------------------------------------
QString Utils::Delete(string s, int pos, int count)
{
        UtilsStd mlb;
	string t = mlb.Delete(s, pos, count);
	return qstring(t);
}
//--------------------------------------------------------------------
QString Utils::Delete(QString s, int pos, int count)
{
	s.remove(pos, count);
	return s;
}
//------------------------------------------------------------------
string Utils:: stdstring(QString qs)
{
	string s;
	QChar * data = qs.data();
	int i = 0;
	while (i < qs.length()) 
		{
			s += (char)data->unicode(); 
			//cout << (char)data->unicode()<< '\n'; 
			++data; 
			i++;
		}
	return s;
}
//-----------------------------------------------------------------
int Utils::getQuantitySubstr(QString substr, QString str)
{
	int res = 0;
	int start = 0;
	int	p = 0;
	while (p != -1 )
	{
		p = str.indexOf(substr, start);
		if (p != -1) 
		{
			res++;
			start = p +1;
		}
	}
	//qMessageBox("getQSS", "substr " + substr + " src = " + str  + " return " + intToStr(res));
	return res;
}
//----------------------------------------------------------------
int Utils::getPosSubstrN(QString substr, QString str, int number)
{
	int c = 0;
	int start = 0;
	int p = -1;
	while (c != number)
	{
		//qMessageBox("getPosSSN", "in WHILE");
		p = str.indexOf(substr,start);
		if (p == -1) break;
		c++;
		start = p + 1;
	}
	return p;
}
//-------------------------------------------------------
int Utils::nextSubstrPos(QString substr, QString src, QString &ctrlstr)
{
	int p = -1;
	int res = p;
	int all = getQuantitySubstr(substr, src);
	int quantityInCtrl = getQuantitySubstr(substr, ctrlstr);
	if (all > quantityInCtrl)
	{
		p = getPosSubstrN(substr, src, quantityInCtrl+1);
		if (p != -1) 
		{
			ctrlstr += substr + " " ;
			res = p;
		}
	}
	return p;
}
//--------------------------------------------------------------
int Utils::qStringToChar(QString s)
{
	data = new char [64000];
	if (s.length() > 64000) return -1;
	string ts = stdstring(s);
	unsigned int i = 0;
	for (i = 0; i < ts.length(); i++)
			data[i] = ts[i];
	size = i;
	data[i] = 0;
	return -1;	
}
//---------------------------------------------------------------
/*QString Utils:: rus(QString rustext)
{
	//qStringToChar(rustext);
	return QString:: fromUtf8(rustext);
}*/
//---------------------------------------------------------------
QString Utils:: rus(QString rustext)
{
    qStringToChar(rustext);
    return QString:: fromUtf8(data);
    //return rustext;
} 

//------------------------------------------------------------------
QString Utils :: fromUtf8(QString rusTextFromDBMySQL)
{
	QString text = rusTextFromDBMySQL;
	QString ret = "";
	for (int i = 0; i < text.length()-1; i+=2)
	{
		QChar ch = text[i];
		//cout<< ch.unicode()<<" ";
		unsigned short left = 0; left = ch.unicode();
		ch = text[i+1];
		unsigned short right = 0; right = ch.unicode();
		unsigned short ucode = 0; ucode = left << 8;
		ucode += right;
		if (ucode == 0) 
		{
			ucode = 4; ucode = ucode << 8; ucode += 39;
		}
		QChar nch(ucode);
		ret += nch;
	}
	return ret;
}
//------------------------------------------------------
QString Utils :: toUtf8(QString text)
{
	QString r = "";
	cout << '\n';
	for (int i = 0; i < text.length(); i++)
	{
		QChar ch = text[i];
		unsigned short ucode = ch.unicode();
		unsigned char right = ucode; 
		ucode = ucode >> 8;
		unsigned char left = ucode; 
		if ( ((left == 39)|| (right == 39))&&(left != 4) )
			qMessageBox(rus("РћС€РёР±РєР°"), rus("РќРµРґРѕСЂР°Р±РѕС‚РєР° С„СѓРЅРєС†РёРё UserLib :: toUtf8"), "error");
		if ((left == 4)&& (right == 39)) 
		{
			left = right = 0;
		}
		r += left;
		//cout << "left = " << left << "intleft = " << (int)left<< '\n';
		//cout << "right = " << right << "intright = " << (int)right<< '\n';
		r += right;
	}
	return r;
}
//-----------------------------------------------------------
void Utils :: replaceAll(QString &str, QChar src, QChar _new)
{
	QString res = "";
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == src) res += _new;
		 else res += str[i];
	}
	str = res;
}
//-------------------------------------------------
void Utils::getScreenSize(QDialog * wnd, int &w, int &h)
{
	int cw = wnd->width();
	int ch = wnd->height();
	wnd->showMaximized();
	w = wnd -> width();
	h = wnd -> height();
	wnd->setGeometry(100,100, cw, ch);
}
//------------------------------------------------------------------
int Utils::hexStrToDec(QString hexString)
{
    int j = hexString.length() - 1;
    int r = 0;
    for (int i = 0; i < hexString.length(); i++)
    {
        int c = (int)pow(16, (int)j);
        int x = hexChar2Int(hexString[i]);
        r += x*c;
        j--;
    }
    return r;
}
//------------------------------------------------------------------
int Utils::hexChar2Int(QChar ch)
{
    if (ch == '0') return 0;
    if (ch == '1') return 1;
    if (ch == '2') return 2;
    if (ch == '3') return 3;
    if (ch == '4') return 4;
    if (ch == '5') return 5;
    if (ch == '6') return 6;
    if (ch == '7') return 7;
    if (ch == '8') return 8;
    if (ch == '9') return 9;
    if (ch == 'A') return 10;
    if (ch == 'B') return 11;
    if (ch == 'C') return 12;
    if (ch == 'D') return 13;
    if (ch == 'E') return 14;
    if (ch == 'F') return 15;
    return 0;
}
//------------------------------------------------------------------
void Utils::getScreenSize(QMainWindow * wnd, int &w, int &h)
{
	int cw = wnd->width();
	int ch = wnd->height();
	wnd->showMaximized();
	w = wnd -> width();
	h = wnd -> height();
	wnd->setGeometry(100,100, cw, ch);
}
//-------------------------------------------------------------------
void trim(QString &str, QChar sim)
{
	QString q = "";
	while (str[0] == sim) str.remove(0,1);
	int i = str.length();	
	while (str[i] == sim) 
	{
		str.remove(i, 1);
		i = str.length();
	}
}
//------------------------------------------------------------------------------------------
QString Utils ::expToDec(QString s)
{
	QRegExp reg("^\\d{1}\\.\\d+e(\\+|\\-)\\d+$");
	return s;
}
//-------------------------------------------------------------------------------------------
QString Utils :: readtextfile(QString fileName, bool silent){
     if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text))
            return file.readAll();
    }
    QString error = "File " + fileName + " not found";
    if (!silent) this->qMessageBox("Error", error, "error");
    return "";
}
//--------------------------------------------------------------------------------------------
int Utils :: writetextfile(QString fileName, QString data, bool append)
{
	QFile file(fileName);
    if (append) {
        file.open(QIODevice::Append);
    } else {
        file.open(QIODevice::WriteOnly);
    }
    QByteArray by = data.toUtf8();
    file.write(by);
    unsigned long sz = file.size();
    file.close();
    return sz;
}
//----------------------------------------------------------------------------------
void Utils :: log(QString text)
{
    QString path = QApplication::applicationDirPath();
    QString flg = this->readtextfile(path + "/data/.l");
    if (flg != "1") return;
    QString s = this->readtextfile(path + "/data/log.txt");
    s += "\n" + text;
    this->writetextfile(path + "/data/log.txt", s);
}
