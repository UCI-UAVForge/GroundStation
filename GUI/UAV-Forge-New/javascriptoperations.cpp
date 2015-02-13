#include "javascriptoperations.h"
//#include <QDebug>
#include <QApplication>
#include <QtWebKitWidgets/QWebFrame>
#include <QtWebKitWidgets/QWebPage>
#include <QtWebKitWidgets/QWebView>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QWebSettings>
#include <QVariant>

JavaScriptOperations::JavaScriptOperations(QWebView *view) {
    this->view = view;
    qDebug() << "In Constructor for jso";
}

JavaScriptOperations::~JavaScriptOperations() {
    delete view;
}

void JavaScriptOperations::addPointToTableHi() {
    qDebug() << "addPointToTable called from JS.";
}

