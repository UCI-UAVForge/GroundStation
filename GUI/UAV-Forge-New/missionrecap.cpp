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
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
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

    int size = 10;
    QVector<double> x(size), y(size);

    x[0] = 4;
    x[1] = 9;
    x[2] = 4;
    x[3] = 5;
    x[4] = 4;
    x[5] = 5;
    x[6] = 3;
    x[7] = 4;
    x[8] = 7;
    x[9] = 2;

    y[0] = 1;
    y[1] = 2;
    y[2] = 4;
    y[3] = 3;
    y[4] = 5;
    y[5] = 8;
    y[6] = 3;
    y[7] = 2;
    y[8] = 9;
    y[9] = 2;

    ui->plot->clearGraphs();
    ui->plot->addGraph();
    ui->plot->graph(0)->setData(x,y);
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    ui->plot->xAxis->setRange(0,10);
    ui->plot->yAxis->setRange(0,10);
}

void MissionRecap::on_stopButton_clicked()
{
    mediaPlayer.stop();

    int size = 10;
    QVector<double> x(size), y(size);


    for(int i = 0; i < size; i++) {
        x[i] = i;
        y[i] = i;
    }

    ui->plot->addGraph();
    ui->plot->graph(0)->setData(x,y);
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    ui->plot->xAxis->setRange(0,10);
    ui->plot->yAxis->setRange(0,10);
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
