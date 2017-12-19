#ifndef FLIGHTPATHWIDGET_H
#define FLIGHTPATHWIDGET_H

#include <QWidget>
#include <vector>
#include <QMenu>
#include <QAction>
#include <QDebug>

#include "interop.h"
#include "mission.h"
//#include "point.hpp"

using namespace std;
namespace Ui {
class FlightPathWidget;
}

class FlightPathWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FlightPathWidget(QWidget *parent = 0);
    ~FlightPathWidget();
    void updateStuff(Interop *interop, QQuickWidget * mapWidget);

private:
    Mission mission;
    Ui::FlightPathWidget *ui;
    Interop *interop;
    QQuickWidget * mapWidget;
    QMenu* buildMenu();

public slots:

private slots:
    void loadNewMission(int i);
    void mission1();
    void mission2();
    void mission3();
    void mission4();
    void clearMissions();
};

#endif // FLIGHTPATHWIDGET_H
