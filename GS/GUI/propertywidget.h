#ifndef PROPERTYWIDGET_H
#define PROPERTYWIDGET_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>
#include <QTextDocument>
#include <QTextStream>
#include <QMessageBox>
namespace Ui {
class PropertyWidget;
}

class PropertyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PropertyWidget(QWidget *parent = 0);
    ~PropertyWidget();
    void loadProperty(QString filename);
    void saveProperty();
    void resetProperty();
    QJsonDocument ImgProperty;
    QJsonObject PropertyObject;
    QTextDocument* orgDoc,*newDoc;
    QTextDocument* getTextDocument();
private:
    Ui::PropertyWidget *ui;


    QString settings;
    void DisplayProperty();
};

#endif // PROPERTYWIDGET_H
