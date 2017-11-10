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

#include "graphwidget.h"
#include "tablewidget.h"
#include "toolbar.h"
#include "timerwidget.h"
#include "interop.h"
#include "mission.h"
#include "udplink.h"
#include "timer.h"
#include "decoder.h"
#include "movementwidget.h"
#include "statuswidget.h"
#include "tcplink.h"

namespace Ui {
class MainDockWindow;
}

class MainDockWindow : public QMainWindow
{
    Q_OBJECT

public:
    QStackedWidget * centralWidget;
    QToolBar * toolBar;
    UdpLink * link;
    TcpLink * tlink;
    explicit MainDockWindow(QWidget *parent = 0);
    ~MainDockWindow();

    QQuickWidget * createQmlWidget(QUrl qmlSource, QWidget * parent = 0);
    QDockWidget * createDockWidget(const QString &title, Qt::DockWidgetArea area, QWidget * child, QWidget * parent);
    void testFind();
    void testMav();
    void sendCommand();

private slots:
    void hideDockWidgets();
    void closeDockWidgets();
    void loadMapObjects(QQuickWidget * mapWidget);
    void Clear(QJsonArray &arr);

private:
    Ui::MainDockWindow *ui;
};

#endif // MAINDOCKWINDOW_H
