#ifndef JAVASCRIPTOPERATIONS_H
#define JAVASCRIPTOPERATIONS_H

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

class JavaScriptOperations : public QObject {
    Q_OBJECT
public:
    JavaScriptOperations(QWebView *view);
    ~JavaScriptOperations();

public slots:
    Q_INVOKABLE void addPointToTableHi();

private:
    QWebView *view;

};

#endif // JAVASCRIPTOPERATIONS_H
