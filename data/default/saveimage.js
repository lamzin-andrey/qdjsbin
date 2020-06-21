function e(i) {return document.getElementById(i);}


function doLog(s) {
	e('doCout').innerHTML = (e('doCout').innerHTML + '<div style="color:blue">' + s + '</div>');
}

function initDoImage() {
	e('doLoadImage').addEventListener('change', doOnSelectImage, true);
	e('doLoadImage').addEventListener('load', doOnLoadFile, true);
}
/**
 *  
*/
function doOnSelectImage() {
	doLog('onselect handler');
	window.doFileReader = new FileReader();
	doFileReader.onloadend = doOnLoadFile;
	doFileReader.readAsDataURL(e('doLoadImage').files[0]);
}

function doOnLoadFile(evt) {
	doLog('OnLoadFile handler');
	window.s = doFileReader.result;
	e('doPreview').src = s;
	doLog('ready image data');
}

function doTestCanvas() {
	var ctx = e('doCanvas').getContext('2d');
	ctx.fillStyle = '#AA0000';
	ctx.fillRect(0, 0, 100, 100);
	window.s = e('doCanvas').toDataURL('image/jpeg');
	doLog('ready canvas data');
}
function testSaveImageFromDataUrl() {
	doLog(window.s);
	var path = Qt.saveFileDialog('Save as..', '/home/andrey', '*.png, *.jpg');
	Qt.savePng(path, window.s, 100);
}
/*
 * QT C++ code
 * 
 * #include <QtCore>
#include <QApplication>

#include <QImage>
#include <QByteArray>
#include <QTextStream>
#include <QDebug>
#include <QLabel>

int main(int argc, char *argv[]) {
    QString filename = "output.png";
    if (argc > 1) {
        filename = argv[1];
    }
    QApplication a(argc, argv);
    QTextStream stream(stdin);
    qDebug() << "reading";
    //stream.readAll();
    qDebug() << "read complete";
    QByteArray base64Data = stream.readAll().toAscii();
    QImage image;
    qDebug() << base64Data;
    image.loadFromData(QByteArray::fromBase64(base64Data), "PNG");
    QLabel label(0);
    label.setPixmap(QPixmap::fromImage(image));
    label.show();
    qDebug() << "writing";
    image.save(filename, "PNG");
    qDebug() << "write complete";
    return a.exec();
}
 * */
