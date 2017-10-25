#include "maindockwindow.h"
#include "ui_maindockwindow.h"
#include <QDebug>


MainDockWindow::MainDockWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainDockWindow)
{
    centralWidget = new QStackedWidget(this);
    toolBar = new ToolBar(this);
    QQuickWidget * mapWidget = createQmlWidget(QUrl("qrc:/res/map.qml"), this);
    centralWidget->addWidget(mapWidget);
    QDockWidget * graphDock = createDockWidget("Graph",Qt::BottomDockWidgetArea, new GraphWidget(this), this);
    QDockWidget * tableDock = createDockWidget("Table",Qt::BottomDockWidgetArea, new TableWidget(this), this);
    QDockWidget * timerDock = createDockWidget("Timer",Qt::RightDockWidgetArea, new TimerWidget(this), this);
    graphDock->setMinimumWidth(500);
    tableDock->setMinimumWidth(500);
    toolBar->addAction(graphDock->toggleViewAction());
    toolBar->addAction(tableDock->toggleViewAction());
    toolBar->addAction(timerDock->toggleViewAction());
    toolBar->addAction("Test find", this, &MainDockWindow::testFind);
    toolBar->addAction("Hide All Widgets", this, &MainDockWindow::hideDockWidgets);
    //toolBar->addAction("Close All Widgets", this, &MainDockWindow::closeDockWidgets);
    addToolBar(toolBar);
    setCentralWidget(centralWidget);
}

QDockWidget * MainDockWindow::createDockWidget(const QString &title, Qt::DockWidgetArea area, QWidget * child, QWidget * parent) {
    QDockWidget * dock = new QDockWidget(title, parent);
    dock->setWidget(child);
    addDockWidget(area, dock);
    dock->setVisible(false);
    return dock;
}

QQuickWidget * MainDockWindow::createQmlWidget(QUrl qmlSource, QWidget * parent) {
    QQuickWidget * quickWidget = new QQuickWidget(parent);
    quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    quickWidget->setSource(qmlSource);
    return quickWidget;
}

void MainDockWindow::testFind() {
    qDebug() << this->findChild<GraphWidget*>();
}

void MainDockWindow::hideDockWidgets() {
    foreach(QDockWidget * dw, this->findChildren<QDockWidget*>()) {
        dw->setVisible(false);
    }
}
void MainDockWindow::closeDockWidgets() {
    foreach(QDockWidget * dw, this->findChildren<QDockWidget*>()) {
        delete dw;
    }
}



MainDockWindow::~MainDockWindow()
{
    delete ui;
}
