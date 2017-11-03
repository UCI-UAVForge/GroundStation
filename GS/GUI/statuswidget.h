#ifndef STATUS_WIDGET_H
#define STATUS_WIDGET_H

#include <QWidget>
#include <QGridLayout>

#include "textbox.h"
#include "mavlink.h"

class StatusWidget : public QWidget
{
    Q_OBJECT
public:
    /// \brief Default constructor. Takes no arguments.
    explicit StatusWidget(QWidget* parent=0);

    QGridLayout * layout;
    TextBox *battery;

public slots:
    void updateStatus(mavlink_sys_status_t status);

};
#endif
