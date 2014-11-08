#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <QWidget>

namespace Ui {
class Tutorial;
}

class Tutorial : public QWidget
{
    Q_OBJECT

public:
    explicit Tutorial(QWidget *parent = 0);
    ~Tutorial();

private:
    Ui::Tutorial *ui;
};

#endif // TUTORIAL_H
