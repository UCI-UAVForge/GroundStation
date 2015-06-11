/* This is the header file for the MainWindow class. For information about
 * this class and its functions, see comments on the top of mainwindow.cpp.
 *
 * File added sometime prior to April 30 2015.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
// <<<<<<< HEAD
#include <QShortcut>
#include <QPixmap>
#include <QDebug>

#include <iostream>
#include <QtWebKitWidgets/QWebView>
#include <QUrl>

#include "options.h"
#include "tutorial.h"
#include "mapplanning.h"
#include "mapexecution.h"
#include "missionrecap.h"

#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //button actions
    void openTutorial();
    void missionPlanningClicked();
    void missionExecutionClicked();
    void missionRecapClicked();

    //quit command
    void on_actionQuit_triggered();

    void checkFinishStatus(int status);

    void showMissionPlanning();
    void showMissionExecution();
    void showMissionRecap();
    void showTutorial();

private:
    Ui::MainWindow *ui;
    QPropertyAnimation *animation;
};

#endif // MAINWINDOW_H
