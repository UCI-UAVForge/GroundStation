#ifndef MAPPLANNING_H
#define MAPPLANNING_H

#include <QDialog>

namespace Ui {
class MapPlanning;
}

class MapPlanning : public QDialog
{
    Q_OBJECT

public:
    explicit MapPlanning(QWidget *parent = 0);
    ~MapPlanning();

private:
    Ui::MapPlanning *ui;
};

#endif // MAPPLANNING_H
