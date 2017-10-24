#ifndef MAINDOCKWINDOW_H
#define MAINDOCKWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QStackedWidget>
#include <QQuickWidget>
#include <QMenu>

#include "toolbar.h"
#include "timerwidget.h"
namespace Ui {
class MainDockWindow;
}

class MainDockWindow : public QMainWindow
{
    Q_OBJECT

public:
    QStackedWidget * centralWidget;
    QToolBar * toolBar;
    explicit MainDockWindow(QWidget *parent = 0);
    ~MainDockWindow();

    QQuickWidget * createQmlWidget(QUrl qmlSource, QWidget * parent = 0);
    void testFind();
private slots:
    void hideDockWidgets();
    void closeDockWidgets();

private:
    Ui::MainDockWindow *ui;
};

#endif // MAINDOCKWINDOW_H
