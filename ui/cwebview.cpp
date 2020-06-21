#include "cwebview.h"

CWebView::CWebView(QWidget *parent) :
    QWebView(parent)
{
    lastKeyCode = -1;
    lastKeyText = "";
}

void CWebView:: contextMenuEvent(QContextMenuEvent *evt) {

}
void CWebView::keyPressEvent(QKeyEvent *evt) {
    lastKeyCode = evt->key();
    lastKeyText = evt->text();
    QWebView::keyPressEvent(evt);
}
