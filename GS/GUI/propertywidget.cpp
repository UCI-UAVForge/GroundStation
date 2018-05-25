#include "propertywidget.h"
#include "ui_propertywidget.h"
#include <QDir>
PropertyWidget::PropertyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PropertyWidget)
{
    ui->setupUi(this);
    loadProperty(QDir::currentPath() + "/../../GroundStation/GS/res/test_property.json");
    DisplayProperty();

}

PropertyWidget::~PropertyWidget()
{
    delete ui;
}

void PropertyWidget::loadProperty(QString filename)
{
    QFile file;
    file.setFileName(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug()<<"failed";
    qDebug()<<"opened!";

    QTextStream ReadFile(&file);
    //settings = ReadFile.readAll();
    settings = file.readAll();
    file.close();
    ImgProperty = QJsonDocument::fromJson(settings.toUtf8());
    PropertyObject = ImgProperty.object();
    newDoc = new QTextDocument(settings);
}

void PropertyWidget::saveProperty()
{
    //QString filename = "new_property.json";
    QString filename = QDir::currentPath() + "/../../GroundStation/GS/res/new_property.json";
    QFile newfile(filename);
    if ( newfile.open(QIODevice::WriteOnly) )
     {
         QTextStream stream( &newfile );
         stream << newDoc->toPlainText() << endl;
         newfile.close();
     }
    else
        QMessageBox(QMessageBox::Warning, "property not saved", "property not saved, try again");

}

void PropertyWidget::resetProperty()
{
 qDebug()<<"start reset";
 newDoc = new QTextDocument(settings);
 ui->textEdit->setDocument(newDoc);
}

QTextDocument* PropertyWidget::getTextDocument()
{
    return ui->textEdit->document();
}

void PropertyWidget::DisplayProperty()
{ 
    ui->textEdit->setDocument(newDoc);
    //ui->textEdit->setText(settings);
    qDebug()<<settings;
}
