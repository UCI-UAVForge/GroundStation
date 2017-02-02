#ifndef GSCONTROLPANEL_H
#define GSCONTROLPANEL_H

#include <QDialog>

namespace Ui {
class GSControlPanel;
}

class GSControlPanel : public QDialog
{
    Q_OBJECT

public:
    explicit GSControlPanel(QWidget *parent = 0);
    ~GSControlPanel();

private:
    Ui::GSControlPanel *ui;
};

#endif // GSCONTROLPANEL_H
