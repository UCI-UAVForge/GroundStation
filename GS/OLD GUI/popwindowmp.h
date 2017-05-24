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
    void on_yesButton_clicked();
    void on_noButton_clicked();

private:
    Ui::PopWindowMP *ui;

signals:
    void windowClosed();
};

#endif // POPWINDOWMP_H
