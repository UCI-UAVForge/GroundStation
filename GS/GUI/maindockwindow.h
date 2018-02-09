#ifndef MAINDOCKWINDOW_H
#define MAINDOCKWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QStackedWidget>
#include <QQuickWidget>
#include <QMenu>
#include <QAction>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <thread>
#include <QDebug>
#include <QQuickItem>
#include <QtCharts>

#include "graphwidget.h"
#include "toolbar.h"
#include "timerwidget.h"
#include "interop.h"
#include "mission.h"
#include "obstacles.h"
#include "timer.h"
#include "decoder.h"
#include "movementwidget.h"
#include "statuswidget.h"
#include "flightpathwidget.h"
#include "actionwidget.h"
#include "qfiwidget.h"
#include "messagewidget.h"
#include "seriallink.h"
#include "wyp.h"
#include "encoder.h"
#include "tcplink.h"
#include "udplink.h"
#include "missionwidget.h"
#include "loginwidget.h"
#include "uavbutton.h"
#include "mapwidget.h"

namespace Ui {
class MainDockWindow;
}

class MainDockWindow : public QMainWindow
{
    Q_OBJECT

public:
    QStackedWidget * centralWidget;
    Link * link;
    Decoder * decoder;
    Encoder * encoder;
    Mission * mission;
    UAVButton * uavButton;
    explicit MainDockWindow(QWidget *parent = 0);
    ~MainDockWindow();

    QQuickWidget * createQmlWidget(QUrl qmlSource, QWidget * parent = 0);
    QDockWidget * createDockWidget(const QString &title, Qt::DockWidgetArea area, QWidget * child, QWidget * parent);
    void testFind();
    void test();

    void changeLink(Link * link, QString hostport);
    void showConnWidget();
    void addToolBarButtons();
    void addInteropLogin();
    void connectDecoder(Decoder * decoder);
    void connectEncoder(Encoder * encoder);
    void connectWaypoint(Waypoint * waypoint, Encoder * encoder, Decoder * decoder);
signals:
    void what(int i);
private slots:
    void hideDockWidgets();
    void closeDockWidgets();
    void updateMovingObjects(QQuickWidget * mapWidget);

private:
    Ui::MainDockWindow *ui;
    Interop * interop;
};

#endif // MAINDOCKWINDOW_H
