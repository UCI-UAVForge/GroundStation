#include "missionrecap.h"
#include "ui_missionrecap.h"
#include "mapexecution.h"
#include "mainwindow.h"

MissionRecap::MissionRecap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MissionRecap)
{
    ui->setupUi(this);
    mediaPlayer.setVideoOutput(ui->VideoWidget);
    //QString fileName = "qrc:/res/videoSample.avi";
    //mediaPlayer.setMedia(QUrl(fileName));
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Movie"),QDir::homePath());
    mediaPlayer.setMedia(QUrl::fromLocalFile(fileName));
    //ui->VideoWidget->show();
    mediaPlayer.play();
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

void MissionRecap::on_pushButton_5_clicked()
{
    MainWindow *mainwindow = new MainWindow();
    this -> close();
    mainwindow->show();
}

void MissionRecap::on_VideoWidget_destroyed()
{

}
