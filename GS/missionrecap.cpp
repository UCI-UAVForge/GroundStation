#include "missionrecap.h"


/**
 * Creates video widget, requests a video to be played back
 * Creates a map to play back UAV path
 * Also creates custom plot for UAV statistics
 */
MissionRecap::MissionRecap(QWidget *parent) : QDialog(parent), ui(new Ui::MissionRecap) {
    ui->setupUi(this);

    //Roman Parise - You get bugs if you turn this on. I have no idea why.

    //mediaPlayer.setVideoOutput(ui->VideoWidget);

    //QString fileName = QFileDialog::getOpenFileName(this, tr("Open Movie"),QDir::homePath());
    //mediaPlayer.setMedia(QUrl::fromLocalFile(fileName));

    ui->VideoWidget->setAspectRatioMode(Qt::IgnoreAspectRatio);
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(updateMediaPlayer(int)), Qt::UniqueConnection);
    connect(&mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(updateSlider(qint64)), Qt::UniqueConnection);

    connect(ui->webView->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addClickListener()), Qt::UniqueConnection);
    ui->webView->load(QUrl("qrc:/res/html/mapsExecution.html"));//

    connect(ui->webView->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addClickListener()), Qt::UniqueConnection);
    ui->webView->load(QUrl("qrc:/res/html/missionRecap.html"));//

    setupRealtimeDataDemo(ui->customPlot);

}

MissionRecap::~MissionRecap() {
    delete ui;
}
/**
 * Checks if QT under QT4.7
 * This is the code for the custom plot chart to play back real time data of the UAV
 * Currently auto plays lines (10/23/15)
 */

void MissionRecap::setupRealtimeDataDemo(QCustomPlot *customPlot) {
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  QMessageBox::critical(this, "", "You're using Qt < 4.7, the realtime data demo needs functions that are available with Qt 4.7 to work properly");
#endif

  customPlot->addGraph(); // blue line
  customPlot->graph(0)->setPen(QPen(Qt::blue));
  customPlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
  customPlot->graph(0)->setAntialiasedFill(false);
  customPlot->addGraph(); // red line
  customPlot->graph(1)->setPen(QPen(Qt::red));
  customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));

  customPlot->addGraph(); // blue dot
  customPlot->graph(2)->setPen(QPen(Qt::blue));
  customPlot->graph(2)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
  customPlot->addGraph(); // red dot
  customPlot->graph(3)->setPen(QPen(Qt::red));
  customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

  customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
  customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
  customPlot->xAxis->setAutoTickStep(false);
  customPlot->xAxis->setTickStep(2);
  customPlot->axisRect()->setupFullAxesBox();

  // make left and bottom axes transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

  // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
  dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

void MissionRecap::realtimeDataSlot() {
  // calculate two new data points:
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  double key = 0;
#else
  double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
#endif
  static double lastPointKey = 0;
  if (key-lastPointKey > 0.01) // at most add point every 10 ms
  {
    double value0 = qSin(key); //qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
    double value1 = qCos(key); //qSin(key*1.3+qCos(key*1.2)*1.2)*7 + qSin(key*0.9+0.26)*24 + 26;
    // add data to lines:
    ui->customPlot->graph(0)->addData(key, value0);
    ui->customPlot->graph(1)->addData(key, value1);
    // set data of dots:
    ui->customPlot->graph(2)->clearData();
    ui->customPlot->graph(2)->addData(key, value0);
    ui->customPlot->graph(3)->clearData();
    ui->customPlot->graph(3)->addData(key, value1);
    // remove data of lines that's outside visible range:
    ui->customPlot->graph(0)->removeDataBefore(key-8);
    ui->customPlot->graph(1)->removeDataBefore(key-8);
    // rescale value (vertical) axis to fit the current data:
    ui->customPlot->graph(0)->rescaleValueAxis();
    ui->customPlot->graph(1)->rescaleValueAxis(true);
    lastPointKey = key;
  }
  // make key axis range scroll with the data (at a constant range size of 8):
  ui->customPlot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
  ui->customPlot->replot();

  // calculate frames per second:
  static int frameCount;
  ++frameCount;

}

void MissionRecap:: updateSlider(qint64 position) {
    ui->horizontalSlider->setValue(position);
}

void MissionRecap:: updateMediaPlayer(int position) {
    mediaPlayer.setPosition(position);
}

// replay button
// redirect to mission execution
void MissionRecap:: replayMissionClicked() {
    this->done(2);
}

// back button
// redirect to main window
void MissionRecap::on_backButton_clicked() {
    mediaPlayer.stop();

    this->done(0);
}

// play button
void MissionRecap::on_playButton_clicked() {
    ui->horizontalSlider->setRange(0, mediaPlayer.duration());
    if(mediaPlayer.state() == QMediaPlayer::PlayingState)
        mediaPlayer.pause();
    else
        mediaPlayer.play();

}

// stop button
void MissionRecap::on_stopButton_clicked() {
    mediaPlayer.stop();

}

void MissionRecap::on_openFileButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Movie"),QDir::homePath());
    mediaPlayer.setMedia(QUrl::fromLocalFile(fileName));
}



// new mission button
// redirect to mission planning window
void MissionRecap::on_newMission_clicked() {
    this->done(1);
    MapPlanning* x = new MapPlanning;
    x->showFullScreen();
}

//Creates the bridge called cbridge between the java script object and this class.
void MissionRecap::addClickListener() {
    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("cbridge",this);
}
