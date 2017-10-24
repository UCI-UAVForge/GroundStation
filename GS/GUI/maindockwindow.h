#ifndef MAINDOCKWINDOW_H
#define MAINDOCKWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainDockWindow;
}

class MainDockWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainDockWindow(QWidget *parent = 0);
    ~MainDockWindow();

private:
    Ui::MainDockWindow *ui;
};

#endif // MAINDOCKWINDOW_H
