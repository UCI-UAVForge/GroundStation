#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "ui_dialog.h"

class Dialog : public QObject
{
    Q_OBJECT

public:
    explicit Dialog(QObject *parent = 0)
        : QObject(parent)
    {
        ui.setupUi(&dialog);
        dialog.show();

        //connect(ui.send, SIGNAL(clicked()), SLOT(clicked()));
    }

    void displayMessage(const QString &message)
    {
        ui.output->appendPlainText(message);
    }

signals:
    /*!
        This signal is emitted from the C++ side and the text displayed on the HTML client side.
    */
    void sendText(const QString &text);
    void sendPoint(double lat, double lng);

public slots:
    /*!
        This slot is invoked from the HTML client side and the text displayed on the server side.
    */
    void receiveText(const QString &text)
    {
        displayMessage(tr("Received message: %1").arg(text));
    }
    void addPointToTable(double lat, double lng){
        displayMessage("Adding new point" + QString::number(lat,'g',10) + ", " + QString::number(lng,'g',10));
    }

private slots:
    /*!
        Note that this slot is private and thus not accessible to HTML clients.
    */
    void clicked()
    {
        const QString text = "";//ui.input->text();

        if (text.isEmpty()) {
            return;
        }
        QStringList parts = text.split(" ");
        if(parts.length() != 2){
            return;
        }
        double lat = ((QString)parts.at(0)).toDouble();
        double lng = ((QString)parts.at(1)).toDouble();
        emit sendPoint(lat,lng);
        //emit sendText(text);
        displayMessage(tr("Sent message: %1").arg(text));

        //ui.input->clear();
    }

private:
    QDialog dialog;

public:
    Ui::Dialog ui;
};

#endif // DIALOG_H
