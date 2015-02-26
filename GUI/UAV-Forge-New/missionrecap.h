#ifndef MISSIONRECAP_H
#define MISSIONRECAP_H

#include <QtWidgets/QWidget>
#include <QtMultimediaWidgets>
#include <QtGui/QMovie>
#include <QVideoWidget>
#include <qmediaplayer.h>
#include <qvideowidget.h>
#include <qvideosurfaceformat.h>

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
    void on_backButton_clicked();
    void on_playButton_clicked();

    void on_stopButton_clicked();

    void on_openFileButton_clicked();

    void on_horizontalSlider_sliderPressed();

private:
    Ui::MissionRecap *ui;
    QMediaPlayer mediaPlayer;
    QVideoFrame currentFrame;
};

#endif // MISSIONRECAP_H
