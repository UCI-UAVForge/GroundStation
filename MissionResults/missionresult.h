#ifndef MISSIONRESULT_H
#define MISSIONRESULT_H

#include <QMainWindow>

namespace Ui {
class missionresult;
}

class missionresult : public QMainWindow
{
    Q_OBJECT

public:
    explicit missionresult(QWidget *parent = 0);
    ~missionresult();

private:
    Ui::missionresult *ui;
};

#endif // MISSIONRESULT_H
