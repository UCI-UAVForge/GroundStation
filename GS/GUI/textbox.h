#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include "mavlink.h"
#include <QLabel>

class TextBox : public QWidget
{
    Q_OBJECT
public:
    explicit TextBox(QWidget *parent = nullptr);
    TextBox(QString t, QString textColor= "black", QWidget *parent = nullptr);
    QLabel * text;
    QLabel * title;

    void setTxt(const QString &t);
    void setBgColor(const QString &color);
signals:

public slots:
};

#endif // TEXTBOX_H
