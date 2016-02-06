#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QtWidgets/QWidget>
#include <QtMultimediaWidgets>
#include <QtGui/QMovie>
#include <QVideoWidget>
#include <qmediaplayer.h>

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QSlider;
class QLabel;
QT_END_NAMESPACE

class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();

public slots:
    void play();
private:
    QMediaPlayer mediaPlayer;
    QAbstractButton *playButton;
    QSlider *positionSlider;
    QLabel *errorLabel;
};

#endif
