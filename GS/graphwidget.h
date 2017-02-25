#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>

#include <qcustomplot.h>

#include "mission.h"

namespace Ui {
class GraphWidget;
}

class GraphWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GraphWidget(QWidget *parent = 0);
    ~GraphWidget();

private slots:
    void makePlot();

private:
    Ui::GraphWidget *ui;

    Mission* getNewMission();
};

#endif // GRAPHWIDGET_H
