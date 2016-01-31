#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>

/*
 * connection to simulation
 * google doc (multiple) protocal notes
 * 1-2 weeks
*/

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QWidget *parent = 0);
    ~ConnectionDialog();

public slots:
    void closeWindow();

private slots:
    void closeConnectionDialog();
    void on_OK_button_clicked();

private:
    Ui::ConnectionDialog *ui;
};

#endif // CONNECTIONDIALOG_H
