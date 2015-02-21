#ifndef POPWINDOWMP_H
#define POPWINDOWMP_H

#include <QWidget>

namespace Ui {
class PopWindowMP;
}

class PopWindowMP : public QWidget
{
    Q_OBJECT
public:
    explicit PopWindowMP(QList<QString> strings, QWidget *parent = 0);
    QList<QString> mapStrings;
    ~PopWindowMP();

private slots:
    void yesButtonClicked();
    void on_pushButton_2_clicked();

private:
    Ui::PopWindowMP *ui;

signals:
    void windowClosed();
};

#endif // POPWINDOWMP_H
