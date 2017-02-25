#ifndef MISSIONSTATUSWINDOW_H
#define MISSIONSTATUSWINDOW_H

#include <QDialog>

namespace Ui {
class MissionStatusWindow;
}

class MissionStatusWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MissionStatusWindow(QWidget *parent = 0);
    ~MissionStatusWindow();

private:
    Ui::MissionStatusWindow *ui;
};

#endif // MISSIONSTATUSWINDOW_H
