#ifndef QTTABTEST_H
#define QTTABTEST_H

#include <QMainWindow>
//#include "options.h"
#include <QPropertyAnimation>
#include <QShortcut>
#include <QPixmap>
#include <QDebug>
#include <iostream>
#include <QUrl>
#include <QMdiArea>

#include "ui_qttabtest.h"

namespace Ui {

    class QtTabTest;

}

class QtTabTest : public QMainWindow {

    Q_OBJECT

public:

    explicit QtTabTest(QWidget *parent = 0);

    ~QtTabTest();

    void addNewTab( QWidget * , QString );

    void deleteTabIndex( int );

    void deleteTabWidget(QWidget* qw);
  
private:

    Ui::QtTabTest *ui;
    bool isFirstTabEmpty ;

};

#endif // QTTABTEST_H
