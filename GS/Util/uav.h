#ifndef UAV_H
#define UAV_H

#include <QDebug>
#include <QQuickWidget>
#include <QQuickItem>
#include <QVariant>

using namespace std;

class UAV
{
public:
    UAV();
    void setWidget(QQuickWidget * widget);
    void updateUAV(float x, float y);

private:
    QQuickWidget * mapWidget;
};

#endif // UAV_H
