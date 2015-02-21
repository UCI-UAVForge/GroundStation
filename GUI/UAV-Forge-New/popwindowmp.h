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
    explicit PopWindowMP(QList<QList<QString> > list, QWidget *parent = 0);
    ~PopWindowMP();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_1_clicked();

private:
    Ui::PopWindowMP *ui;
    QList<QList<QString> > list;
};

#endif // POPWINDOWMP_H
