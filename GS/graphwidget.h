#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QVector>

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

public slots:
    void appendPoint(double x, double y, int id);

private slots:
    void makePlot(int id);

private:
    Ui::GraphWidget *ui;

    /**
     * @brief data A 2d vector of the form data[id][index]. id specifies the graph that
     * the datapoint belongs to. index specifies the index of the datapoint.
     */
    QVector<QVector<double>> data;

    Mission* getNewMission();
};

#endif // GRAPHWIDGET_H
