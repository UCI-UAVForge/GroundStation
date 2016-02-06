#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QWidget *parent = 0);
    ~ConnectionDialog();

private slots:
    void closeConnectionDialog();
    void on_OK_button_clicked();

private:
    Ui::ConnectionDialog *ui;
};

#endif // CONNECTIONDIALOG_H
