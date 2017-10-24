#include "maindockwindow.h"
#include "ui_maindockwindow.h"
#include <QDebug>
#include <QAction>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>

#include "graphwidget.h"

MainDockWindow::MainDockWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainDockWindow)
{
    centralWidget = new QStackedWidget(this);
    toolBar = new ToolBar(this);
    QQuickWidget * mapWidget = createQmlWidget(QUrl("qrc:/res/map.qml"), this);
    centralWidget->addWidget(mapWidget);
    QDockWidget * graphDock = new QDockWidget("Graph", this);
    GraphWidget * graphWidget = new GraphWidget(this);
    graphDock->setWidget(graphWidget);
    addDockWidget(Qt::BottomDockWidgetArea, graphDock);
    graphDock->setVisible(false);
    graphDock->setFixedSize(500, 300);
    toolBar->addAction(graphDock->toggleViewAction());
    toolBar->addAction("Test find", this, &MainDockWindow::testFind);
    toolBar->addAction("Hide All Widgets", this, &MainDockWindow::hideDockWidgets);
    //toolBar->addAction("Close All Widgets", this, &MainDockWindow::closeDockWidgets);
    addToolBar(toolBar);
    setCentralWidget(centralWidget);
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
