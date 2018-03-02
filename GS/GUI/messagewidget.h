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
    void updateMessages_str(QString text);

public slots:
    void updateClearMission(bool success);

private:
    Ui::MessageWidget *ui;
};

#endif // MESSAGEWIDGET_H
