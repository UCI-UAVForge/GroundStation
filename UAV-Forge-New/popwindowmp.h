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
    explicit PopWindowMP(QWidget *parent = 0);
    ~PopWindowMP();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::PopWindowMP *ui;
};

#endif // POPWINDOWMP_H
