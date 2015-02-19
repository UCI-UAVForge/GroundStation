#include "missionrecap.h"
#include "ui_missionrecap.h"
#include "mapexecution.h"
#include "mainwindow.h"

MissionRecap::MissionRecap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MissionRecap)
{
    ui->setupUi(this);
    //ui->VideoWidget->resize(321, 171);
    mediaPlayer.setVideoOutput(ui->VideoWidget);
    //QString fileName = "qrc:/res/videoSample.mp4";
    //mediaPlayer.setMedia(QUrl(fileName));
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Movie"),QDir::homePath());
    mediaPlayer.setMedia(QUrl::fromLocalFile(fileName));
    ui->VideoWidget->setAspectRatioMode(Qt::IgnoreAspectRatio);
}

MissionRecap::~MissionRecap()
{
    delete ui;
}

void MissionRecap:: replayMissionClicked()
{
    this->close();
    mapexecution *mapExecution = new mapexecution();
    mapExecution->show();
}

void MissionRecap::on_backButton_clicked()
{
    mediaPlayer.stop();
    MainWindow *mainwindow = new MainWindow();
    this -> close();
    mainwindow->show();
}

void MissionRecap::on_playButton_clicked()
{
    if(mediaPlayer.state() == QMediaPlayer::PlayingState)
        mediaPlayer.pause();
    else
        mediaPlayer.play();
}

void MissionRecap::on_stopButton_clicked()
{
    mediaPlayer.stop();
}
