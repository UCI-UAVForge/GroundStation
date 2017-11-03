#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include "mavlink.h"
#include <QLabel>
#include <QGroupBox>

struct TextBox : public QWidget {
    QLabel * text;
    QLabel * title;
    TextBox(QString t) {
        title = new QLabel(t);
        text = new QLabel("N/A");
        title->setAlignment(Qt::AlignHCenter);
        title->setStyleSheet("QLabel {font-size:8pt;}");
        text->setAlignment(Qt::AlignHCenter);
        text->setStyleSheet("QLabel {font-size: 14pt; color: blue;}");
        QVBoxLayout* vbox = new QVBoxLayout();
        vbox->addWidget(title);
        vbox->addWidget(text);
        setLayout(vbox);
        setStyleSheet("QWidget {background-color: white;}");
    }
    void setTxt(QString t) {
        text->setText(t);
    }
};

class InfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InfoWidget(QWidget *parent = nullptr);
    QGridLayout *layout;
    TextBox *alt, *lon, *lat, *vel;

signals:

public slots:
    void updateTelemetry(mavlink_gps_raw_int_t gps);
};

#endif // INFOWIDGET_H
