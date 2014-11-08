#ifndef MISSIONRECAP_H
#define MISSIONRECAP_H

#include <QWidget>

namespace Ui {
class MissionRecap;
}

class MissionRecap : public QWidget
{
    Q_OBJECT

public:
    explicit MissionRecap(QWidget *parent = 0);
    ~MissionRecap();

private:
    Ui::MissionRecap *ui;
};

#endif // MISSIONRECAP_H
