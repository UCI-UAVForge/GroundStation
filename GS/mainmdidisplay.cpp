#include "mainmdidisplay.h"
#include "ui_mainmdidisplay.h"
#include "mapwidget.h"
#include "tablewidget.h"

MainMDIDisplay::MainMDIDisplay(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainMDIDisplay) {

    ui->setupUi(this);

    ui->mdiArea->setBackground(QBrush( QPixmap( ":/res/images/UAVLogo.png" ) ) );

    map = new MapWidget();
    addWindow(map);

    TableWidget *tw = new TableWidget();
    addWindow(tw);

    addWindow(&msw);

    addWindow(&gscp);

    this->connect(map, &MapWidget::pointAdded, tw, &TableWidget::appendRow);
    this->connect(map, &MapWidget::JSInitialized, this, &MainMDIDisplay::setupMapPaths);
}

MainMDIDisplay::~MainMDIDisplay() {
    delete ui;
    exit(0);
}

void MainMDIDisplay::setupMapPaths(){
    map->sendCreateNewPath(0);
    map->sendSetActivePath(0);
}

void MainMDIDisplay::addWindow(QWidget* myNewWindowWidget) {
    /* TODO Default window style should go here by making all of the windows conform to the same
     * stylesheet - Roman Parise */
    /* Second argument - turns off the 'X' in the subwindows */
    ui->mdiArea->addSubWindow(myNewWindowWidget, Qt::CustomizeWindowHint|Qt::WindowMinMaxButtonsHint);
}

//TODO Right now this function doesn't work due to issues with Qt's private constructors for QMdiSubWindow. - Roman Parise
void MainMDIDisplay::addWindow(QWidget* myNewWindowWidget, QString windowTitle) {
    /* Second argument - turns off the 'X' in the subwindows */
    QMdiSubWindow tempSubWindow ;
    tempSubWindow.setWidget(myNewWindowWidget);
    tempSubWindow.setWindowTitle(windowTitle);
    this->addWindow(&tempSubWindow);
}
