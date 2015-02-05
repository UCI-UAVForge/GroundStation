#include "videoplayer.h"

#include <QtWidgets>
#include <qvideowidget.h>
#include <QVideoWidget>
#include <qvideosurfaceformat.h>

VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget(parent)
    , mediaPlayer(0, QMediaPlayer::VideoSurface)
    , playButton(0)
    , positionSlider(0)
    , errorLabel(0)
{
    QVideoWidget *videoWidget = new QVideoWidget;
    mediaPlayer.setVideoOutput(videoWidget);
    /*
    connect(&mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(mediaStateChanged(QMediaPlayer::State)));
    connect(&mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(&mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    connect(&mediaPlayer, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(handleError()));
    */
}

VideoPlayer::~VideoPlayer()
{
}

void VideoPlayer::play()
{
    //QString fileName = "qrc:/res/videoSample.mp4";
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Movie"),QDir::homePath());

    mediaPlayer.setMedia(QUrl(fileName));
    playButton->setEnabled(true);
/*
    switch(mediaPlayer.state()) {
    case QMediaPlayer::PlayingState:
        mediaPlayer.pause();
        break;
    default:
        mediaPlayer.play();
        break;
    }
    */
}
