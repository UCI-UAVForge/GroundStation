#ifndef MISSIONTAB_H
#define MISSIONTAB_H

#include <QWidget>

namespace Ui {
class MissionTab;
}

class MissionTab : public QWidget
{
    Q_OBJECT

public:
    explicit MissionTab(QWidget *parent = 0);
    ~MissionTab();

private:
    Ui::MissionTab *ui;
};

#endif // MISSIONTAB_H
