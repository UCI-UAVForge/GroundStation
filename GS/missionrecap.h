#ifndef MISSIONRECAP_H
#define MISSIONRECAP_H

#include <QObject>
#include <QtWidgets/QWidget>
#include <QtMultimediaWidgets>
#include <QtGui/QMovie>
#include <QVideoWidget>
#include <qmediaplayer.h>
#include <qvideowidget.h>
#include <qvideosurfaceformat.h>
#include <iostream>
#include <QTimer>

#include "mapexecution.h"
#include "qcustomplot.h"
#include "mapplanning.h"
#include "videoplayer.h"
#include "qcustomplot.h"

#include "ui_missionrecap.h"

#define QCUSTOMPLOT_COMPILE_LIBRARY

namespace Ui {
class MissionRecap;
}


class MissionRecap : public QDialog
{
    Q_OBJECT

public:
    explicit MissionRecap(QWidget *parent = 0);
    ~MissionRecap();

public slots:
    void updateSlider(qint64 position);
    void updateMediaPlayer(int position);
    void replayMissionClicked();
    void setupRealtimeDataDemo(QCustomPlot *customPlot);


private slots:
    void realtimeDataSlot();
    void on_backButton_clicked();
    void on_playButton_clicked();
    void on_stopButton_clicked();
    void on_openFileButton_clicked();

    void on_newMission_clicked();

    void addClickListener();

private:
    Ui::MissionRecap *ui;
    QMediaPlayer mediaPlayer;
    QVideoFrame currentFrame;
    QTimer dataTimer;
};

#endif // MISSIONRECAP_H
