#ifndef POSLAYOUTBOX_H
#define POSLAYOUTBOX_H


#include <QGridLayout>
#include <QLabel>


class posLayoutBox: public QGridLayout
{
    Q_OBJECT
public:
    posLayoutBox(QString t, QString la, QString lo, QWidget *parent = nullptr);

private:
    QLabel *title, *lat, *lon;

public slots:
    void setLatLon(QString la, QString lo);
};

#endif // POSLAYOUTBOX_H
