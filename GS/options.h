#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>

#include "mapplanning.h"
#include "mapexecution.h"
#include "missionrecap.h"

namespace Ui {
class Options;
}

class Options : public QWidget
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = 0);
    ~Options();

private slots:
    void missionPlanningClicked();
    void missionExecutionClicked();
    void missionRecapClicked();
private:
    Ui::Options *ui;

};

#endif // OPTIONS_H
