#ifndef CLICKABLEQLABEL_H
#define CLICKABLEQLABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>

class clickableQLabel : public QLabel
{
    Q_OBJECT
public:
    clickableQLabel();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // CLICKABLEQLABEL_H
