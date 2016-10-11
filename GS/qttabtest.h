#ifndef QTTABTEST_H
#define QTTABTEST_H

#include <QMainWindow>

namespace Ui {
class QtTabTest;
}

class QtTabTest : public QMainWindow
{
    Q_OBJECT

public:
    explicit QtTabTest(QWidget *parent = 0);
    ~QtTabTest();

private:
    Ui::QtTabTest *ui;
};

#endif // QTTABTEST_H
