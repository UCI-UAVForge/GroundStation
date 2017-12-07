#include "flightpathwidget.h"
#include "ui_flightpathwidget.h"

FlightPathWidget::FlightPathWidget(QWidget *parent) : QWidget(parent), ui(new Ui::FlightPathWidget), interop(nullptr), mapWidget(nullptr)
{
    ui->setupUi(this);
    QMenu * menu = buildMenu();
    ui->Mission_->setMenu(menu);
}

FlightPathWidget::~FlightPathWidget()
{
    delete ui;
}

void FlightPathWidget::updateStuff(Interop *inte, QQuickWidget *mapW){
    interop = inte;
    mapWidget=mapW;
}

QMenu* FlightPathWidget::buildMenu(){
    QMenu* menu = new QMenu(this);

    QAction * action = new QAction("No Mission", this);
    action->setIconText("No Mission");
    connect(action, SIGNAL(triggered()), this, SLOT(clearMissions()));
    menu->addAction(action);

    action = new QAction("Mission 1", this);
    action->setIconText("Mission 1");
    connect(action, SIGNAL(triggered()), this, SLOT(mission1()));
    menu->addAction(action);

    action = new QAction("Mission 2", this);
    action->setIconText("Mission 2");
    connect(action, SIGNAL(triggered()), this, SLOT(mission2()));
    menu->addAction(action);

    action = new QAction("Mission 3", this);
    action->setIconText("Mission 3");
    connect(action, SIGNAL(triggered()), this, SLOT(mission3()));
    menu->addAction(action);

    action = new QAction("Mission 4", this);
    action->setIconText("Mission 4");
    connect(action, SIGNAL(triggered()), this, SLOT(mission4()));
    menu->addAction(action);

    return menu;

}

void FlightPathWidget::mission1(){
    if (ui->Mission_->text()!="Mission 1"){
        loadNewMission(1);
    }
}

void FlightPathWidget::mission2(){
    if (ui->Mission_->text()!="Mission 2"){
        loadNewMission(2);
    }

}

void FlightPathWidget::mission3(){
    if (ui->Mission_->text()!="Mission 3"){
        loadNewMission(3);
    }
}

void FlightPathWidget::mission4(){
    if (ui->Mission_->text()!="Mission 4"){
        loadNewMission(4);
    }
}

void FlightPathWidget::clearMissions(){
    ui->Mission_->setText("No Mission");
}

void FlightPathWidget::loadNewMission(int i){
    mission.clearMission(mapWidget);
    if (interop!=nullptr)
        mission.setMission(interop->getMission(i));
    if (mapWidget!=nullptr && !mission.DNE()){
        mission.clearMission(mapWidget);
        mission.loadMissionObjects(mapWidget);
    }
    ui->Mission_->setText("Mission "+QString::number(i));

}


