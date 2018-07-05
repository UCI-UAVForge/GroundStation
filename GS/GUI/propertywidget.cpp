#include "propertywidget.h"
#include "ui_propertywidget.h"
#include <QDir>
#include <QFile>
PropertyWidget::PropertyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PropertyWidget)
{
    ui->setupUi(this);
    loadProperty();
    DisplayProperty();

}

PropertyWidget::~PropertyWidget()
{
    delete ui;
}

void PropertyWidget::loadProperty()
{
    QString filename = QDir::currentPath() + "/../../GroundStation/GS/res/test_property" + QString::number(propertyNum)+".json";
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

void PropertyWidget::loadNextProperty()
{
    propertyNum++;
    if(!QFile::exists(QDir::currentPath() + "/../../GroundStation/GS/res/test_property" + QString::number(propertyNum)+".json"))
    {
        propertyNum=1;
    }
    loadProperty();
    DisplayProperty();
}

void PropertyWidget::saveProperty()
{
    //QString filename = "new_property.json";
    QString filename = QDir::currentPath() + "/../../GroundStation/GS/res/test_property" + QString::number(propertyNum)+".json";
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

QString PropertyWidget::propertyfileName()
{
    return QDir::currentPath() + "/../../GroundStation/GS/res/test_property" + QString::number(propertyNum)+".json";
}

void PropertyWidget::DisplayProperty()
{ 
    ui->textEdit->setDocument(newDoc);
    //ui->textEdit->setText(settings);
    qDebug()<<settings;
}
