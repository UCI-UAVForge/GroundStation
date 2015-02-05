#ifndef MISSIONRECAP_H
#define MISSIONRECAP_H

#include <QtWidgets/QWidget>
#include <QtMultimediaWidgets>
#include <QtGui/QMovie>
#include <QVideoWidget>
#include <qmediaplayer.h>

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

    void on_VideoWidget_destroyed();

private:
    Ui::MissionRecap *ui;
    QMediaPlayer mediaPlayer;
};

#endif // MISSIONRECAP_H
