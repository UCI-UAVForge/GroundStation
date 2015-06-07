#include "missionrecap.h"

MissionRecap::MissionRecap(QWidget *parent) : QWidget(parent), ui(new Ui::MissionRecap) {
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

    setupRealtimeDataDemo(ui->customPlot);
}

MissionRecap::~MissionRecap() {
    delete ui;
}



void MissionRecap::setupRealtimeDataDemo(QCustomPlot *customPlot) {
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  QMessageBox::critical(this, "", "You're using Qt < 4.7, the realtime data demo needs functions that are available with Qt 4.7 to work properly");
#endif
  //demoName = "Real Time Data Demo";

  // include this section to fully disable antialiasing for higher performance:
  /*
  customPlot->setNotAntialiasedElements(QCP::aeAll);
  QFont font;
  font.setStyleStrategy(QFont::NoAntialias);
  customPlot->xAxis->setTickLabelFont(font);
  customPlot->yAxis->setTickLabelFont(font);
  customPlot->legend->setFont(font);
  */
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
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  /*if (key-lastFpsKey > 2) // average fps over 2 seconds
  {
    ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
          .arg(ui->customPlot->graph(0)->data()->count()+ui->customPlot->graph(1)->data()->count())
          , 0);
    lastFpsKey = key;
    frameCount = 0;
  }*/
}

void MissionRecap:: updateSlider(qint64 position) {
    ui->horizontalSlider->setValue(position);
}

void MissionRecap:: updateMediaPlayer(int position) {
    mediaPlayer.setPosition(position);
}

void MissionRecap:: replayMissionClicked() {
    this->close();
    mapexecution *mapExecution = new mapexecution();
    mapExecution->showFullScreen();
}

void MissionRecap::on_backButton_clicked() {
    mediaPlayer.stop();
    MainWindow *mainwindow = new MainWindow();
    this -> close();
    mainwindow->showFullScreen();
}

void MissionRecap::on_playButton_clicked() {
    ui->horizontalSlider->setRange(0, mediaPlayer.duration());
    if(mediaPlayer.state() == QMediaPlayer::PlayingState)
        mediaPlayer.pause();
    else
        mediaPlayer.play();
/*
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
    */
}

void MissionRecap::on_stopButton_clicked() {
    mediaPlayer.stop();

    /*
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
    */
}

void MissionRecap::on_openFileButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Movie"),QDir::homePath());
    mediaPlayer.setMedia(QUrl::fromLocalFile(fileName));
}

void MissionRecap::on_horizontalSlider_sliderPressed() {

}

void MissionRecap::on_newMission_clicked() {
    MapPlanning *mapPlanning = new MapPlanning();
    this -> close();
    mapPlanning->showFullScreen();
}

void MissionRecap::on_pushButton_5_clicked() {
    MainWindow *mainwindow = new MainWindow();
    this -> close();
    mainwindow->showFullScreen();
}

//Creates the bridge called cbridge between the java script object and this class.
void MissionRecap::addClickListener() {
    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("cbridge",this);
}
