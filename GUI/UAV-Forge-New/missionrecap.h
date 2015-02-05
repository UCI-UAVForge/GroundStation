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
public slots:
    void replayMissionClicked();
private slots:
    void on_pushButton_5_clicked();

private:
    Ui::MissionRecap *ui;
};

#endif // MISSIONRECAP_H
