#include "missionrecap.h"
#include "ui_missionrecap.h"
#include "mapexecution.h"
#include "mainwindow.h"
#include <iostream>
#include "mapplanning.h"
#include "videoplayer.h"
#define QCUSTOMPLOT_COMPILE_LIBRARY
#include "qcustomplot.h"

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
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(updateMediaPlayer(int)));
    connect(&mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(updateSlider(qint64)));

    connect(ui->webView->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addClickListener()));
    ui->webView->load(QUrl("qrc:/res/html/mapsExecution.html"));

    connect(ui->webView->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addClickListener()));
    ui->webView->load(QUrl("qrc:/res/html/missionRecap.html"));


    int size = 10;
    QVector<double> x(size), y(size);

    for(int i = 0; i < size; i++) {
        x[i] = i;
        y[i] = i;
    }

    ui->plot->addGraph();
    ui->plot->graph(0)->setData(x,y);
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
    ui->plot->xAxis->setRange(0,10);
    ui->plot->yAxis->setRange(0,10);
}

MissionRecap::~MissionRecap()
{
    delete ui;
}

void MissionRecap:: updateSlider(qint64 position){
    ui->horizontalSlider->setValue(position);
}

void MissionRecap:: updateMediaPlayer(int position){
    mediaPlayer.setPosition(position);
}

void MissionRecap:: replayMissionClicked()
{
    this->close();
    mapexecution *mapExecution = new mapexecution();
    mapExecution->showFullScreen();
}

void MissionRecap::on_backButton_clicked()
{
    mediaPlayer.stop();
    MainWindow *mainwindow = new MainWindow();
    this -> close();
    mainwindow->showFullScreen();
}

void MissionRecap::on_playButton_clicked()
{
    ui->horizontalSlider->setRange(0, mediaPlayer.duration());
    if(mediaPlayer.state() == QMediaPlayer::PlayingState)
        mediaPlayer.pause();
    else
        mediaPlayer.play();
}

void MissionRecap::on_stopButton_clicked()
{
    mediaPlayer.stop();
}

void MissionRecap::on_openFileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Movie"),QDir::homePath());
    mediaPlayer.setMedia(QUrl::fromLocalFile(fileName));
}

void MissionRecap::on_horizontalSlider_sliderPressed()
{

}

void MissionRecap::on_newMission_clicked()
{
    MapPlanning *mapPlanning = new MapPlanning();
    this -> close();
    mapPlanning->showFullScreen();
}

void MissionRecap::on_pushButton_5_clicked()
{
    MainWindow *mainwindow = new MainWindow();
    this -> close();
    mainwindow->showFullScreen();
}
