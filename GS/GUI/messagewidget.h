#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>
#include "mavlink.h"
//#include "qtmaterialscrollbar.h"

namespace Ui {
class MessageWidget;
}

class MessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MessageWidget(QWidget *parent = 0);
    ~MessageWidget();

    void updateMessages(mavlink_statustext_t stattext);
private:
    Ui::MessageWidget *ui;
};

#endif // MESSAGEWIDGET_H
